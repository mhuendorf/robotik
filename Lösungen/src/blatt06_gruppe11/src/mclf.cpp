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

#include <dynamic_reconfigure/server.h>
#include <blatt06_gruppe11/DynConfigConfig.h>


struct PointEx {
  geometry_msgs::Point32 point;
  double weight{0.0};

  static PointEx build(geometry_msgs::Point32 point, double weight = 0.0) {
    return {point, weight};
  }
};

static std::random_device rng_device_{};
static std::mt19937 rng_{rng_device_()};

static double g_sigma = 0.6; // Standardabweisung
static bool ready_{false};
static double max_weight_{0};
static std::vector<PointEx> points_;
static std::unique_ptr<geometry_msgs::TransformStamped> T_P1_to_OdomC{nullptr};

// ----------------------------------------------------------------------------

double get_next_double() {
  std::uniform_real_distribution<double> dist(0.0, 1.0);
  return dist(rng_);
}

bool dblEqual(float a, float b, float epsilon = 0.01) {
    return fabs(a - b) <= ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
}

// ----------------------------------------------------------------------------

void dynCallback(blatt06_gruppe11::DynConfigConfig &config) {
  g_sigma = config.sigma;

  ROS_INFO_STREAM("Dyn. sigma change: " << g_sigma);
}

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

void resample();
void sensor_update();
void get_robot_position(ros::Publisher& pub);

void callback(const geometry_msgs::PoseWithCovarianceStamped& msg, ros::Publisher& pub_pos) {
  if (!ready_) {
    return;
  }

  static geometry_msgs::Point32 g_lastPoint;

  // Throttle, um nicht OOM zu laufen
  if (!dblEqual(g_lastPoint.x, msg.pose.pose.position.x) || 
    !dblEqual(g_lastPoint.y, msg.pose.pose.position.y) ||
    !dblEqual(g_lastPoint.z, msg.pose.pose.position.z)) {
    geometry_msgs::Point32 p;
    p.x = msg.pose.pose.position.x;
    p.y = msg.pose.pose.position.y;
    p.z = msg.pose.pose.position.z;
    points_.push_back(PointEx::build(p, 0.5));
    max_weight_ = std::max(0.5, max_weight_);

    g_lastPoint = p;

    // ROS_INFO_STREAM(points_.size());
  }

  // ROS_INFO_STREAM(msg);

  geometry_msgs::PoseStamped p2_in_OdomC;
  p2_in_OdomC.header = msg.header;
  p2_in_OdomC.pose = msg.pose.pose;

  if (T_P1_to_OdomC != nullptr && !points_.empty()) {
    geometry_msgs::TransformStamped T_W_to_P1 = inv(*T_P1_to_OdomC.get());
    geometry_msgs::PoseStamped p2_in_p1;

    // p2_in_p1 = T_W_to_P1 * p2_in_OdomC
    tf2::doTransform(p2_in_OdomC, p2_in_p1, T_W_to_P1);
    // ROS_INFO_STREAM(p2_in_p1);

    // ROS_INFO_STREAM("\n####################\n\n");

    for (PointEx& val : points_) {
      auto& p = val.point;
      geometry_msgs::TransformStamped pose_in_map;
      pose_in_map.header = msg.header;
      pose_in_map.transform.translation.x = p.x;
      pose_in_map.transform.translation.y = p.y;
      pose_in_map.transform.translation.z = p.z;

      pose_in_map.transform.rotation.x = 0;
      pose_in_map.transform.rotation.y = 0;
      pose_in_map.transform.rotation.z = 0;
      pose_in_map.transform.rotation.w = 1;

      geometry_msgs::PoseStamped out;
      tf2::doTransform(p2_in_p1, out, pose_in_map);

      // motion update
      p.x = out.pose.position.x;
      p.y = out.pose.position.y;
      p.z = out.pose.position.z;

      // ROS_INFO_STREAM("-------------------------\n" << p);
      // ROS_INFO_STREAM(pose_in_map);
      // ROS_INFO_STREAM(out);
    }
  } else if (T_P1_to_OdomC == nullptr) {
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

  sensor_update();
  resample();
  get_robot_position(pub_pos);
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

void resample() {
  if (points_.empty() || max_weight_ <= 0.001) {
    return;
  }

  std::vector<PointEx> result = points_;
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

void get_robot_position(ros::Publisher& pub) {
  auto it = std::max_element(points_.begin(), points_.end(), [](auto const& lhs, auto const& rhs) {
    return lhs.weight < rhs.weight;
  });
  if (it != points_.end()) {
    const auto& p = (*it).point;

    geometry_msgs::PoseStamped pose;
    pose.header.stamp = ros::Time::now();
    pose.header.frame_id = "odom_combined";
    pose.pose.position.x = p.x;
    pose.pose.position.y = p.y;
    pose.pose.position.z = p.z;

    pose.pose.orientation.x = 0;
    pose.pose.orientation.y = 0;
    pose.pose.orientation.z = 0;
    pose.pose.orientation.w = 1;

    pub.publish(pose);
  }

  // NOTE: Teil C:
  // Gewichteter Mittelwert:
  //   - Messungenauigkeiten werden berücksichtigt und entsprechend gewichtet
  //   - Wert kann eine hohe Abweichung haben
  //   - aufwendige(rere) Berechnung
  // Partikel mit bestem Gewicht: 
  //   - bester Wert wird ausgewählt
  //   - schnell
}

void callback_a(const geometry_msgs::PoseWithCovarianceStamped& msg, ros::Publisher& pub) {
  geometry_msgs::Point32 p;
  p.x = msg.pose.pose.position.x;
  p.y = msg.pose.pose.position.y;
  p.z = msg.pose.pose.position.z;
  points_.push_back(PointEx::build(p, 0.5));
  max_weight_ = std::max(0.5, max_weight_);
  ready_ = true;

  ROS_INFO_STREAM("Initial Pose: " << p);

  // Partikel generieren
  std::normal_distribution<> distX(p.x, g_sigma);
  std::normal_distribution<> distY(p.y, g_sigma);
  // std::normal_distribution<> distZ(p.z, g_sigma);
  size_t len = get_next_double() * 20;
  for (size_t i = 0; i < len; ++i) {
    p = {};
    p.x = distX(rng_);
    p.y = distY(rng_);
    p.z = 0.0; // distZ(rng_);
    points_.push_back(PointEx::build(p, 0.5));
  }

  // Daten veröffentlichen
  uint32_t pose_size = std::min(std::max(1u, static_cast<uint32_t>(points_.size()) / 2), 1000u);
  geometry_msgs::PoseArray result;
  result.header.stamp = ros::Time::now();
  result.header.frame_id = "odom_combined";
  result.poses.resize(pose_size);

  for (const PointEx& p : points_) {
    geometry_msgs::Pose pose;
    pose.position.x = p.point.x;
    pose.position.y = p.point.y;
    pose.position.z = p.point.z;

    pose.orientation.x = 0;
    pose.orientation.y = 0;
    pose.orientation.z = 0;
    pose.orientation.w = 1;
  
    result.poses.push_back(pose);
  }
  pub.publish(result);
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "nr2");
  ros::NodeHandle n;
  ros::Publisher pub = n.advertise<geometry_msgs::PoseArray>("outPoseArray", 1);
  ros::Publisher pub_pos = n.advertise<geometry_msgs::PoseStamped>("outPosition", 1);
  ros::Subscriber sub_a = n.subscribe<geometry_msgs::PoseWithCovarianceStamped, const geometry_msgs::PoseWithCovarianceStamped&>("/initialpose", 1, std::bind(callback_a, std::placeholders::_1, pub));
  ros::Subscriber sub_b = n.subscribe<geometry_msgs::PoseWithCovarianceStamped, const geometry_msgs::PoseWithCovarianceStamped&>("/robot_pose_ekf/odom_combined", 1, std::bind(callback, std::placeholders::_1, pub_pos));

  dynamic_reconfigure::Server<blatt06_gruppe11::DynConfigConfig> server;
  server.setCallback(std::bind(&dynCallback, std::placeholders::_1));

  ros::spin();
  return 0;
}
