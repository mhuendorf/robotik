#include <ros/ros.h>
#include <tf2_ros/transform_listener.h>
#include <geometry_msgs/TransformStamped.h>
#include <geometry_msgs/PointStamped.h>
#include <tf2_ros/buffer.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>

void sensorCallback(const geometry_msgs::PointStamped& msg) {
  tf2_ros::Buffer tfBuffer;
  tf2_ros::TransformListener tfListener(tfBuffer);
  geometry_msgs::PointStamped pointOut;
  try {
    // FIXME: "gripper" passed to lookupTransform argument target_frame does not exist.

    // pointOut = tfBuffer.lookupTransform("gripper", msg.header.frame_id, msg.header.stamp);
    tfBuffer.transform(msg, pointOut, "gripper", ros::Duration(0.0));
    ROS_INFO_STREAM("Ergebnis: " << 
      pointOut.point.x << ", " <<
      pointOut.point.y << ", " <<
      pointOut.point.z
    );
  } catch (tf2::TransformException &ex) {
    ROS_WARN("%s", ex.what());
  }
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "gripper_distance");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("sensor_channel", 1, sensorCallback);

  ros::spin();
  return 0;
}