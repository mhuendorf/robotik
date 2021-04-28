#include "ros/ros.h"
#include "sensor_msgs/Imu.h"


void imuCallback(const sensor_msgs::Imu& msg) {
  ROS_INFO_STREAM("Got message: " << msg);
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "imu_print");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("/imu", 1, imuCallback);

  ros::spin();

  return 0;
}
