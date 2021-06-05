#include "ros/ros.h"

#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>

#include "sensor_msgs/Imu.h"
#include "nav_msgs/Odometry.h"


class Kalmanfilter {

    private:
    ros::Subscriber sub_imu;
    ros::Subscriber sub_odom;
    ros::NodeHandle nh;

    sensor_msgs::Imu imu_msg;
    

    public:
    Kalmanfilter() : nh() {
        sub_imu = nh.subscribe("/imu/data", 100, &Kalmanfilter::callback1, this);
        sub_odom = nh.subscribe("/odom", 100, &Kalmanfilter::callback2, this);
        // information output
        ROS_INFO("Node started...");
        imu_msg.orientation.x = 0;
        ros::spin();
    };

    /*    Header header

    geometry_msgs/Quaternion orientation
    float64[9] orientation_covariance # Row major about x, y, z axes

    geometry_msgs/Vector3 angular_velocity
    float64[9] angular_velocity_covariance # Row major about x, y, z axes

    geometry_msgs/Vector3 linear_acceleration
    float64[9] linear_acceleration_covariance # Row major x, y z */



    /*     Header header
    string child_frame_id
    geometry_msgs/PoseWithCovariance pose
    geometry_msgs/TwistWithCovariance twist */

    void callback1(const sensor_msgs::Imu& msg_imu) {
        ROS_INFO("test1");
        std::cout << "test" << std::endl;
        /*static tf2_ros::TransformBroadcaster br;
        geometry_msgs::TransformStamped transformStamped;

        transformStamped.header.stamp = ros::Time::now();
        transformStamped.header.frame_id = "world";
        */
    }

    void callback2(const nav_msgs::Odometry& msg_odom) {
        ROS_INFO("test2");
        /*static tf2_ros::TransformBroadcaster br;
        geometry_msgs::TransformStamped transformStamped;

        transformStamped.header.stamp = ros::Time::now();
        transformStamped.header.frame_id = "world";
        */
    }
};

int main(int argc, char **argv) {

    ros::init(argc, argv, "kalman_node");

    Kalmanfilter k;
    ros::spin();
    return 0;
    }
