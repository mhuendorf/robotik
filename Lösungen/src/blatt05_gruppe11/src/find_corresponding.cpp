#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/PointStamped.h>
#include <tf2_ros/transform_listener.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <visualization_msgs/Marker.h>

std::vector<sensor_msgs::LaserScan> *laserVec;
std::vector<std::vector<geometry_msgs::Point>> *laserPoints;
std::vector<sensor_msgs::LaserScan> *modelVec;
std::vector<std::vector<geometry_msgs::Point>> *modelPoints;

tf2_ros::Buffer *buffer;
tf2_ros::TransformListener *listener;


void laserCallback(const sensor_msgs::LaserScan msg)
{
    float inc = msg.angle_increment;
    float start = msg.angle_min;
    float current = msg.angle_min;
    std::vector<geometry_msgs::Point> currentPoints;
    for(float point : msg.ranges)
    {
        geometry_msgs::Point transformed;
        transformed.z = 0;
        transformed.x = point * std::cos(current);
        transformed.y = point * std::sin(current);
        currentPoints.push_back(transformed);
        current += msg.angle_increment;
    } 
    laserPoints->push_back(currentPoints);
    laserVec->push_back(msg);
}

void modelCallback(const sensor_msgs::LaserScan msg)
{
    float inc = msg.angle_increment;
    float start = msg.angle_min;
    float current = msg.angle_min;
    std::vector<geometry_msgs::Point> currentPoints;
    for(float point : msg.ranges)
    {
        geometry_msgs::Point transformed;
        transformed.z = 0;
        transformed.x = point * std::cos(current);
        transformed.y = point * std::sin(current);
        currentPoints.push_back(transformed);
        current += msg.angle_increment;
    }
    modelPoints->push_back(currentPoints);
    modelVec->push_back(msg);
}

int main(int argc, char **argv){
    std::cout << "find_corresponding" << std::endl;

    laserVec = new std::vector<sensor_msgs::LaserScan>();
    modelVec = new std::vector<sensor_msgs::LaserScan>();
    laserPoints = new std::vector<std::vector<geometry_msgs::Point>>();
    modelPoints = new std::vector<std::vector<geometry_msgs::Point>>();

    ros::init(argc, argv, "find_corresponding");
    ros::NodeHandle n;
    ros::Subscriber laserSub = n.subscribe<sensor_msgs::LaserScan>("/scan", 1, laserCallback);
    ros::Subscriber modelSub = n.subscribe<sensor_msgs::LaserScan>("/model", 1, modelCallback);
    ros::Publisher chatter_pub = n.advertise<visualization_msgs::Marker>("corresponding", 0);
    while(ros::ok()){
        // get the laser float ranges
        if(laserPoints->size() > 0 && modelPoints->size() > 0){
        std::vector<geometry_msgs::Point> current = laserPoints->front();
        std::vector<geometry_msgs::Point> compare = modelPoints->front();
            while(current.size() > 0){
                geometry_msgs::Point currentPoint = current.front();
                float closestDistance = INFINITY;
                geometry_msgs::Point closestPoint;

                for(geometry_msgs::Point p : compare)
                {
                    float distance = std::sqrt(std::pow(currentPoint.x - p.x, 2) + std::pow(currentPoint.y - p.y, 2));
                    if(distance < closestDistance)
                    {
                        closestDistance = distance;
                        closestPoint = p;
                    }
                }
                visualization_msgs::Marker marker;
                marker.type = visualization_msgs::Marker::ARROW;
                marker.pose.position.x = currentPoint.x;
                marker.pose.position.y = currentPoint.x;
                marker.pose.position.z = currentPoint.z;
                marker.pose.orientation.x = closestPoint.x;
                marker.pose.orientation.y = closestPoint.y;
                marker.pose.orientation.z = closestPoint.z;
                marker.color.r = 1.0;
                marker.color.g = 0.0;
                marker.color.b = 0.0;
                marker.color.a = 1.0;
                chatter_pub.publish(marker);
            }
        }
        ros::spinOnce();
    }

    return 0;
}