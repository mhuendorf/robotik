#include <cmath>

#include "ros/ros.h"
#include "sensor_msgs/Imu.h"

int g_counter = 1;
double g_meanX = 0;
double g_meanY = 0;
double g_meanZ = 0;
double g_varianceX = 0;
double g_varianceY = 0;
double g_varianceZ = 0;

double getMean(double i, double lastMean, double value) {
  return ((i - 1.0) / i) * lastMean + (value / i);
}

double getVariance(double i, double lastVariance, double lastMean, double mean, double value) {
  return ((i - 1.0) / i) * (lastVariance + std::pow(lastMean, 2)) + (std::pow(value, 2) / i) - std::pow(mean, 2);
}

void imuCallback(const sensor_msgs::Imu& msg) {
  double currentMeanX = getMean(g_counter, g_meanX, msg.linear_acceleration.x);
  double currentMeanY = getMean(g_counter, g_meanY, msg.linear_acceleration.y);
  double currentMeanZ = getMean(g_counter, g_meanZ, msg.linear_acceleration.z);

  double currentVarianceX = getVariance(g_counter, g_varianceX, g_meanX, currentMeanX, msg.linear_acceleration.x);
  double currentVarianceY = getVariance(g_counter, g_varianceY, g_meanY, currentMeanY, msg.linear_acceleration.y);
  double currentVarianceZ = getVariance(g_counter, g_varianceZ, g_meanZ, currentMeanZ, msg.linear_acceleration.z);

  ROS_INFO_STREAM(
    "Mean / Variance\n" <<
    " x: " << currentMeanX << ", " << currentVarianceX << "\n" <<
    " y: " << currentMeanY << ", " << currentVarianceY << "\n" <<
    " z: " << currentMeanZ << ", " << currentVarianceZ
  );

  ++g_counter;
  g_meanX = currentMeanX;
  g_meanY = currentMeanY;
  g_meanZ = currentMeanZ;
  g_varianceX = currentVarianceX;
  g_varianceY = currentVarianceY;
  g_varianceZ = currentVarianceZ;
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "imu_mean");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("/android/imu", 1, imuCallback);

  ros::spin();
  return 0;
}