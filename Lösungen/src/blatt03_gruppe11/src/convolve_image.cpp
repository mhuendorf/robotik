#include <cmath>
#include <vector>
#include <limits>

#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>

#include <cv_bridge/cv_bridge.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
// #include <opencv2/highgui/highgui.hpp>


void callback(const sensor_msgs::Image& msg, const std::vector<char>& kernel, ros::Publisher& pub) {
  cv::Mat mat_msg;
  try {
    mat_msg = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8)->image;
  } catch (cv_bridge::Exception& e) {
    ROS_ERROR("cv_bridge exception: %s", e.what());
    return;
  }

  // Create kernel matrix
  const uint32_t kernel_size = std::round(std::sqrt(kernel.size()));
  if (kernel_size * kernel_size != kernel.size()) {
    throw std::runtime_error("Invalid matrix size.");
  }
  const cv::Mat_<char> mat_kernel(kernel_size, kernel_size, const_cast<char*>(&kernel[0]));

  // Transform image
  cv::Mat mat_out;
  cv::filter2D(mat_msg, mat_out, -1, mat_kernel, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT);

  // static bool __debugBoolean = true;
  // if (__debugBoolean) {
  //   __debugBoolean = false;
  //   cv::imshow("Debug", mat_out);
  // }

  // Publish transformed image
  sensor_msgs::Image::Ptr out_img = cv_bridge::CvImage(msg.header, "bgr8", mat_out).toImageMsg();
  pub.publish(out_img);
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "convolve_image");
  ros::NodeHandle n;
  ros::NodeHandle np("~");

  // Read kernel parameter
  std::vector<int> buf_kernel;
  np.param<std::vector<int>>("kernel", buf_kernel, { 0,0,0, 1,1,1, 0,0,0});
  std::vector<char> kernel(buf_kernel.size());
  for (size_t i = 0; i < buf_kernel.size(); ++i) {
    kernel[i] = static_cast<char>(buf_kernel[i]);
  }
  
  ros::Publisher pub = n.advertise<sensor_msgs::Image>("imgOut", 100);
  ros::Subscriber sub = n.subscribe<sensor_msgs::Image, const sensor_msgs::Image&>(
    "/camera/rgb/image_rect_color", 100, std::bind(callback, std::placeholders::_1, kernel, pub)
  );

  ros::spin();
  return 0;
}
