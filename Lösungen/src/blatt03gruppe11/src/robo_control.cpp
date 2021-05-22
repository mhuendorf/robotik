#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "geometry_msgs/Twist.h"

#include <math.h>


void callback(const sensor_msgs::LaserScan& msg, ros::NodeHandle& nh, ros::Publisher& pub) {
    /* LaserScan:

    std_msgs/Header header
    uint32 seq
    time stamp
    string frame_id
    float32 angle_min
    float32 angle_max
    float32 angle_increment
    float32 time_increment
    float32 scan_time
    float32 range_min
    float32 range_max
    float32[] ranges
    float32[] intensities
    */

    geometry_msgs::Twist tmsg;
    geometry_msgs::Vector3 linear;
    geometry_msgs::Vector3 angular;


    int points_in_range = 100;

    //int laser_entry_length = (sizeof(msg.ranges)/sizeof(*msg.ranges));
    ROS_INFO_STREAM(/*laser_entry_length << " " << */msg.ranges.size());

    // look in front and see if direction needs to change -> if any laserpoint in front is closer than .5m change direction
    bool front_ok = true;
    for (size_t i = msg.ranges.size()/2-points_in_range/2; i < msg.ranges.size()/2+points_in_range/2; i++)
    {
        if (msg.ranges[i] < 0.5)
        {
            front_ok = false;
            break;
        }
        
    }

    ROS_INFO_STREAM("front_ok: " << front_ok ? "true" : "false");

    if (!front_ok)
    {
        // calculate angle in which the 7 neighboring points are the furthest and no single point of it is closer than .5m
        float max = 0;
        float angle = 0;
        for (size_t i = points_in_range/2; i < msg.ranges.size()-points_in_range/2; i++)
        {
            float add = 0;
            bool isValid = true;
            for (size_t j = 0; j < points_in_range; j++)
            {
                //ROS_INFO_STREAM(i-3+j);
                if (msg.ranges[i-points_in_range/2+j] < 0.5) isValid = false;
                add += msg.ranges[i-points_in_range/2+j];
            }
            if (isValid && max < add)
            {
                max = add;
                angle = msg.angle_min + msg.angle_increment * i;
            }
        }

        // if there is no valid direction, perform a turn
        if (max == 0 || angle == 0)
        {
            angular.z = 1;
        } else {
        angular.z = angle;
        }
    } else {
        linear.x = 0.5;
    }

    tmsg.linear = linear;
    tmsg.angular = angular;


  /* Twist:

  geometry_msgs/Vector3 linear
  float64 x
  float64 y
  float64 z
geometry_msgs/Vector3 angular
  float64 x
  float64 y
  float64 z
*/

  // publish filtered msg
  pub.publish(tmsg);
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "robo_control_node");

  // private NodeHandle
  ros::NodeHandle nh;
  ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
  ros::Subscriber sub = nh.subscribe<sensor_msgs::LaserScan, const sensor_msgs::LaserScan&>("scan", 1000, std::bind(callback, std::placeholders::_1, nh, pub));

  // information output
  ROS_INFO("automatic control started");
  ros::spin();
  return 0;
}