#include <cstdio>
#include <ros/ros.h>
#include <geometry_msgs/TransformStamped.h>
#include <tf2_ros/static_transform_broadcaster.h>
#include <tf2/LinearMath/Quaternion.h>

int main(int argc, char **argv) {
  ros::init(argc, argv, "robot_tf");
  static tf2_ros::StaticTransformBroadcaster broadcaster;

  tf2::Quaternion quat;
  geometry_msgs::TransformStamped tsSensor;
  tsSensor.header.stamp = ros::Time::now();
  tsSensor.header.frame_id = "base";
  tsSensor.child_frame_id = "sensor";
  tsSensor.transform.translation.x = 0;
  tsSensor.transform.translation.y = 0;
  tsSensor.transform.translation.z = 0.5;
  quat.setRPY(0, 0.78539816339745, 0);
  tsSensor.transform.rotation.x = quat.x();
  tsSensor.transform.rotation.y = quat.y();
  tsSensor.transform.rotation.z = quat.z();
  tsSensor.transform.rotation.w = quat.w();
  broadcaster.sendTransform(tsSensor);

  geometry_msgs::TransformStamped tsGripper;
  tsGripper.header.stamp = ros::Time::now();
  tsGripper.header.frame_id = "base";
  tsGripper.child_frame_id = "gripper";
  tsGripper.transform.translation.x = 0.3;
  tsGripper.transform.translation.y = 0;
  tsGripper.transform.translation.z = 0;
  quat.setRPY(0, 0, 0);
  tsGripper.transform.rotation.x = quat.x();
  tsGripper.transform.rotation.y = quat.y();
  tsGripper.transform.rotation.z = quat.z();
  tsGripper.transform.rotation.w = quat.w();
  broadcaster.sendTransform(tsGripper);
  
  ros::spin();
  return 0;
};