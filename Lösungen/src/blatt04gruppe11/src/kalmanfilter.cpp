#include "ros/ros.h"

#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>

#include "sensor_msgs/Imu.h"
#include "nav_msgs/Odometry.h"

using namespace message_filters;

class Kalmanfilter {


    private:
    Subscriber<sensor_msgs::Imu> sub1;
    Subscriber<nav_msgs::Odometry> sub2;
    typedef sync_policies::ApproximateTime<sensor_msgs::Imu, nav_msgs::Odometry> MySyncPolicy;
    typedef Synchronizer<MySyncPolicy> Sync;
    boost::shared_ptr<Sync> sync;

    ros::NodeHandle nh;
    struct curr_state
    {
        float x;
        float y;
        float angle;
    };
    

    public:
    Kalmanfilter() : nh() , sub1(nh, "/imu/data", 1000), sub2(nh, "/odom", 1000) {
    
        //sub_imu = nh.subscribe("/imu/data", 100, &Kalmanfilter::callback1, this);
        //sub_odom = nh.subscribe("/odom", 100, &Kalmanfilter::callback2, this);

        sync.reset(new Sync(MySyncPolicy(1000), sub1, sub2));
        //sync->registerCallback(boost::bind(&Kalmanfilter::callback, this, _1, _2));

        // information output
        ROS_INFO("Node started...");
        ros::spin();
    };

        void callback(const sensor_msgs::Imu& msg_imu, const nav_msgs::Odometry& msg_odom) {
        ROS_INFO("test");

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
    }
    
};

int main(int argc, char **argv) {

    ros::init(argc, argv, "kalman_node");
    Kalmanfilter k;
    ros::spin();
    return 0;
    }
