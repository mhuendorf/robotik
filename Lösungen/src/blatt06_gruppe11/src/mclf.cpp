#include <cmath>
#include <memory>
#include <vector>
#include <random>
#include <unordered_set>

#include <ros/ros.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <geometry_msgs/Point32.h>
#include <geometry_msgs/PoseArray.h>
#include <geometry_msgs/Pose.h>

#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <Eigen/Dense>

//
// TODO:
// - Konfiguration für Standardabweichung (Nr. 2a)
// - Bewegungsschätzung (Nr. 2b)
// - Nr 4 - siehe `sensor_update` für b)
//

constexpr double kSigma = 0.1; // Standardabweisung

struct PointEx {
  geometry_msgs::Point32 point;
  double weight{0.0};

  static PointEx build(geometry_msgs::Point32 point, double weight = 0.0) {
    return {point, weight};
  }
};

static std::random_device rng_device_{};
static std::mt19937 rng_{rng_device_()};
static double max_weight_{0};
static std::vector<PointEx> points_;
static std::unique_ptr<geometry_msgs::TransformStamped> T_P1_to_OdomC{nullptr};

// ----------------------------------------------------------------------------

std::unordered_set<uint32_t> get_random_sample(uint32_t size, uint32_t n, std::mt19937& g) {
  std::unordered_set<uint32_t> sample;
  for (uint32_t i = size - n; i < size; ++i) {
    uint32_t rng_index = std::uniform_int_distribution<uint32_t>(0, i)(g);
    if (sample.find(rng_index) == sample.end()) {
      sample.insert(rng_index);
    } else {
      sample.insert(i);
    }
  }
  return sample;
}

double get_next_double() {
  std::uniform_real_distribution<double> dist(0.0, 1.0);
  return dist(rng_);
}

// ----------------------------------------------------------------------------

void convert(const geometry_msgs::Transform& from, Eigen::Affine3d& to) {
  Eigen::Vector3d trans(from.translation.x, from.translation.y, from.translation.z);
  Eigen::Quaterniond rot(from.rotation.x, from.rotation.y, from.rotation.z, from.rotation.w);
  to.setIdentity();
  to.linear() = rot.toRotationMatrix();
  to.translation() = trans;
}

void convert(const Eigen::Affine3d& from, geometry_msgs::Transform& to) {
  Eigen::Quaterniond q(from.rotation());
  to.rotation.x = q.x();
  to.rotation.y = q.y();
  to.rotation.z = q.z();
  to.rotation.w = q.w();
  to.translation.x = from.translation().x();
  to.translation.y = from.translation().y();
  to.translation.z = from.translation().z();
}

geometry_msgs::TransformStamped inv(const geometry_msgs::TransformStamped& t) {
  Eigen::Affine3d t_eig;
  convert(t.transform, t_eig);
  geometry_msgs::TransformStamped t_inv;
  convert(t_eig.inverse(), t_inv.transform);

  // Switch source and target frame
  t_inv.header.frame_id = t.child_frame_id;
  t_inv.child_frame_id = t.header.frame_id;
  t_inv.header.stamp = t.header.stamp;
  return t_inv;
}

void callback(const geometry_msgs::PoseWithCovarianceStamped& msg, ros::Publisher& pub) {
  // ROS_INFO_STREAM("Pose 2: " << msg);

  geometry_msgs::PoseStamped p2_in_OdomC;
  p2_in_OdomC.header = msg.header;
  p2_in_OdomC.pose = msg.pose.pose;

  if (T_P1_to_OdomC != nullptr) {
    geometry_msgs::TransformStamped T_W_to_P1 = inv(*T_P1_to_OdomC.get());
    geometry_msgs::PoseStamped p2_in_p1;

    // p2_in_p1 = T_W_to_P1 * p2_in_OdomC
    tf2::doTransform(p2_in_OdomC, p2_in_p1, T_W_to_P1);
    // ROS_INFO_STREAM(p2_in_p1);
  } else {
    T_P1_to_OdomC = std::make_unique<geometry_msgs::TransformStamped>();
  }

  // p2 -> p1
  T_P1_to_OdomC->header.frame_id = msg.header.frame_id;
  T_P1_to_OdomC->child_frame_id = "P1";
  T_P1_to_OdomC->transform.translation.x = p2_in_OdomC.pose.position.x;
  T_P1_to_OdomC->transform.translation.y = p2_in_OdomC.pose.position.y;
  T_P1_to_OdomC->transform.translation.z = p2_in_OdomC.pose.position.z;
  
  T_P1_to_OdomC->transform.rotation.x = p2_in_OdomC.pose.orientation.x;
  T_P1_to_OdomC->transform.rotation.y = p2_in_OdomC.pose.orientation.y;
  T_P1_to_OdomC->transform.rotation.z = p2_in_OdomC.pose.orientation.z;
  T_P1_to_OdomC->transform.rotation.w = p2_in_OdomC.pose.orientation.w;

  // TODO: Nr. 2b

  // motion_update();
}

void sensor_update() {
  // Nr. 4b)
  // Simulieren Sie dazu von jedem Partikel aus einen LaserScan in der Karte und
  // vergleichen Sie diesen mit dem echten Scan.
  //  FIXME: Was???
  
  // Wenn die simulierten Werte denen des echten Scans entsprechen soll die Gewichtung 1 sein.
  // Sind die Werte jedoch sehr verschieden, soll das Gewicht gegen 0 gehen.

  max_weight_ = 0.0;
  for (PointEx& p : points_) {
    double probability = get_next_double();
    if (probability > 0.4) {
      // Entspricht echten Wert
      p.weight = 1;
      max_weight_ = 1;
    } else {
      // TODO: Gewicht ist die Formel V
      p.weight = 0.5;

      max_weight_ = std::max(p.weight , max_weight_);
    }
  }
  
}

void motion_update() {
  // TODO: Verschiebe alle Punke um ??? aus Nr. 2b) odom
  float diffX = 1.0;
  float diffY = 0.0;
  float diffZ = 0.0;

  for (auto& p : points_) {
    p.point.x += diffX;
    p.point.y += diffY;
    p.point.z += diffZ;
  }
}

void resample() {
  if (points_.empty() || max_weight_ == 0) {
    return;
  }

  std::vector<PointEx> result = points_;
  // get random index
  int index = get_next_double() * points_.size();
  double beta = 0.0;
  for (int i = 0; i < points_.size(); ++i) {
    beta += get_next_double() * 2 * max_weight_;
    while (beta > points_[i].weight) {
      beta -= points_[i].weight;
      index = (index + 1) % points_.size();
    }
    result[i] = points_[index];
  }

  // Aktualisiere Partikel-Array
  points_ = result;
}

void callback_a(const geometry_msgs::PoseWithCovarianceStamped& msg, ros::Publisher& pub) {
  // motion_update();

  geometry_msgs::Point32 p;
  p.x = msg.pose.pose.position.x;
  p.y = msg.pose.pose.position.y;
  p.z = msg.pose.pose.position.z;
  points_.push_back(PointEx::build(p, 0));
  ROS_INFO_STREAM("Pose 1: " << p);

  resample();

  // Daten veröffentlichen
  uint32_t pose_size = std::min(std::max(1u, static_cast<uint32_t>(points_.size()) / 2), 1000u);
  geometry_msgs::PoseArray result;
  result.header.stamp = ros::Time::now();
  result.header.frame_id = msg.header.frame_id;
  result.poses.resize(pose_size);

  auto indices = get_random_sample(points_.size(), pose_size, rng_);
  for (int index : indices) {
    auto& p = points_.at(index);
    geometry_msgs::Pose pose;
    pose.position.x = p.point.x;
    pose.position.y = p.point.y;
    pose.position.z = p.point.z;

    pose.orientation.x = 0;
    pose.orientation.y = 0;
    pose.orientation.z = 0;
    pose.orientation.w = 0;
  
    result.poses.push_back(pose);
  }
  pub.publish(result);
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "nr2");
  ros::NodeHandle n;
  ros::Publisher pub_a = n.advertise<geometry_msgs::PoseArray>("outPoseArray", 1);
  ros::Publisher pub = n.advertise<geometry_msgs::PoseWithCovarianceStamped>("tbdtbd", 1);
  ros::Subscriber sub_a = n.subscribe<geometry_msgs::PoseWithCovarianceStamped, const geometry_msgs::PoseWithCovarianceStamped&>("/initialpose", 1, std::bind(callback_a, std::placeholders::_1, pub_a));
  ros::Subscriber sub_b = n.subscribe<geometry_msgs::PoseWithCovarianceStamped, const geometry_msgs::PoseWithCovarianceStamped&>("/robot_pose_ekf/odom_combined", 1, std::bind(callback, std::placeholders::_1, pub));

  ros::spin();
  return 0;
}
