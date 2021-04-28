#include <ros/ros.h>
#include <geometry_msgs/TransformStamped.h>
#include <geometry_msgs/PointStamped.h>
#include <turtlesim/Spawn.h>

int main(int argc, char** argv) {
  ros::init(argc, argv, "sensor_node");

  ros::NodeHandle node;
  ros::Publisher pub = node.advertise<geometry_msgs::PointStamped>("sensor_channel", 10);

  ros::Rate rate(10.0);
  while (node.ok()){
    geometry_msgs::PointStamped msg;
    msg.header.stamp = ros::Time::now();
    msg.header.frame_id = "sensor";
    msg.point.x = 0.7071;
    msg.point.y = 0;
    msg.point.z = 0;
    pub.publish(msg);

    rate.sleep();
  }
  return 0;
};