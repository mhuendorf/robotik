#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "geometry_msgs/Twist.h"

#include <math.h>

bool turning;
int turning_pubs;

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


    const float range_in_front = 0.5;
    const float look_goal_distance = 0.5;
    const int points_in_front = 100;
    const int number_of_considered_neighbors = points_in_front;

    // look in front and see if direction needs to change -> if any laserpoint in front is closer than .7m change direction
    bool front_ok = true;
    for (size_t i = msg.ranges.size()/2-points_in_front/2; i < msg.ranges.size()/2+points_in_front/2; i++)
    {
        if (msg.ranges[i] < range_in_front)
        {
            front_ok = false;
            break;
        }
        
    }

    if (!front_ok && !turning)
    {
        // calculate angle in which the 7 neighboring points are the furthest and no single point of it is closer than .5m
        float max = 0;
        float angle = 0;
        bool turning_manoeuvre = true;
        for (size_t i = number_of_considered_neighbors/2; i < msg.ranges.size()-number_of_considered_neighbors/2; i++)
        {
            float add = 0;
            bool isValid = true;
            for (size_t j = 0; j < number_of_considered_neighbors; j++)
            {
                if (msg.ranges[i-number_of_considered_neighbors/2+j] < look_goal_distance) isValid = false;
                add += msg.ranges[i-number_of_considered_neighbors/2+j];
            }
            if (isValid && max < add)
            {
                turning_manoeuvre = false;
                max = add;
                angle = msg.angle_min + msg.angle_increment * i;
            }
        }

        // for pretty output
        std::cout << "                        \r";

        // if there is no valid direction, perform a turn
        if (turning_manoeuvre || (angle > -msg.angle_increment && angle < msg.angle_increment))
        {
            std::cout << "bitte wenden" << "\r";
            turning_pubs = 12;
            turning = true;
            angular.z = 1;
        } else {
            if (angle < 0)
            {
                std::cout << "links rum" << "\r";
            } else {
                std::cout << "rechts rum" << "\r";
            }
        angular.z = angle;
        }
    } else {
        if (turning)
        {
            std::cout << "bitte wenden" << "\r";
            angular.z = 1;
            turning_pubs -=1;
            if (turning_pubs == 0)
            {
                turning = false;
            }
            
        } else {
            std::cout << "einfach cruisen" << "\r";
            linear.x = 0.5;
        }
    }
    std::cout.flush();

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
  ROS_INFO("automatic control started:");
  ros::spin();
  turning = false;
  return 0;
}