#include "ros/ros.h"

#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>

#include "sensor_msgs/Imu.h"
#include "nav_msgs/Odometry.h"

#include <Eigen/Dense>

// Dimensionen Zustand (x, y, theta)
#define N 3
// Dimensionen Aktion (delta x, delta y, delta theta)
#define M 3
// Dimensionen Messung?
#define L 3

using namespace message_filters;

class Kalmanfilter {

    private:
    bool is_first;
    ros::NodeHandle nh;
    sensor_msgs::Imu last_imu;
    nav_msgs::Odometry::ConstPtr last_odom;
    Eigen::MatrixXd A;
    Eigen::MatrixXd B;
    Eigen::MatrixXd H;
    Eigen::MatrixXd Sigma_u;
    Eigen::MatrixXd Sigma_z;
    Eigen::MatrixXd Sigma_t;
    Eigen::VectorXd pose;


    /**
     * Forlmeln für den Kalmanfilter sind implementiert -jedeoch: rechnet auf leeren Matritzen
     * 
     * TODO: Fülle Matritzen mit Daten aus der aus der Imu msg und der Odometry msgs
     * offene Fragen:   Was sind in diesem Fall Aktionen, bzw wo kommen die her? Aktionen können soweit ich weiß nicht der Odometry oder der Imu entnommen werden.
     *                  Was ist die Anfangspose, bzw mit welcher Kovarianz?
     */
    void make_prediction_and_correction(const sensor_msgs::Imu::ConstPtr& msg_imu, const nav_msgs::Odometry::ConstPtr& msg_odom) {

        // a-priori

        // Aktion u z.B. Rotation
        Eigen::VectorXd u(M);
        u(2) = 1;

        auto pose_bar = A * pose + B * u;
        auto Sigma_t_bar = A*Sigma_t*A.transpose() + Sigma_u;

        // Kalman Gewinnmatrix
        auto K = Sigma_t_bar * H.transpose()*(H*Sigma_t_bar*H.transpose() + Sigma_z).inverse();

        // Messung z Beispielhaft 0
        Eigen::VectorXd z(L);

        // a-posteriori
        //Mittelwert
        pose = pose_bar + K*(z-H*pose_bar);

        // Kovarianzmatrix
        Sigma_t = (Eigen::MatrixXd::Identity(K.row(0).size(), K.col(0).size())-K*H)*Sigma_t_bar;
    } 
    

    public:
    Kalmanfilter() : nh(), is_first(true), pose(3), A(N, N) , B(N, M), H(L, N) , Sigma_u(N, N) , Sigma_z(L, L), Sigma_t(N, N){
    
        // subscribe
        Subscriber<sensor_msgs::Imu> sub1(nh, "/imu/data", 1000);
        Subscriber<nav_msgs::Odometry> sub2(nh, "/odom", 1000);
        
        // make synchronizer
        typedef sync_policies::ApproximateTime<sensor_msgs::Imu, nav_msgs::Odometry> MySyncPolicy;
        typedef Synchronizer<MySyncPolicy> Sync;
        boost::shared_ptr<Sync> sync;
        sync.reset(new Sync(MySyncPolicy(1000), sub1, sub2));

        // register it
        sync->registerCallback(boost::bind(&Kalmanfilter::callback, this, _1, _2));

        // information that the node is running
        ROS_INFO("Node started...");
        ros::spin();
    };

    void callback(const sensor_msgs::Imu::ConstPtr& msg_imu, const nav_msgs::Odometry::ConstPtr& msg_odom) {
        if (is_first)
        {
            // TODO: initialize pose and Sigma_t
            is_first = false;
            last_imu.header = msg_imu->header;
            last_imu.orientation = msg_imu->orientation;
            last_imu.orientation_covariance = msg_imu->orientation_covariance;
            last_imu.angular_velocity = msg_imu->angular_velocity;
            last_imu.angular_velocity_covariance = msg_imu-> angular_velocity_covariance;
            last_imu.linear_acceleration = msg_imu->linear_acceleration;
            last_imu.linear_acceleration_covariance = msg_imu->linear_acceleration_covariance;
            ROS_INFO("saved current state");
        } else {
            make_prediction_and_correction(msg_imu, msg_odom);
        }
        // TODO: publish tf with tf broadcaster
    }
    
};

int main(int argc, char **argv) {

    ros::init(argc, argv, "kalman_node");
    Kalmanfilter k;
    ros::spin();
    return 0;
}


/* Imu

Header header

geometry_msgs/Quaternion orientation
float64[9] orientation_covariance # Row major about x, y, z axes

geometry_msgs/Vector3 angular_velocity
float64[9] angular_velocity_covariance # Row major about x, y, z axes

geometry_msgs/Vector3 linear_acceleration
float64[9] linear_acceleration_covariance # Row major x, y z */

/* Odometry

Header header
string child_frame_id
geometry_msgs/PoseWithCovariance pose
geometry_msgs/TwistWithCovariance twist */
