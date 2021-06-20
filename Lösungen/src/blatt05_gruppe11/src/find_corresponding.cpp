#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/PointStamped.h>
#include <tf2_ros/transform_listener.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <visualization_msgs/Marker.h>

std::vector<sensor_msgs::LaserScan> *laserVec;
std::vector<std::vector<geometry_msgs::PointStamped>> *laserPoints;
std::vector<sensor_msgs::LaserScan> *modelVec;
std::vector<std::vector<geometry_msgs::PointStamped>> *modelPoints;

tf2_ros::Buffer *buffer;
tf2_ros::TransformListener *listener;

void laserCallback(const sensor_msgs::LaserScan msg)
{
    float inc = msg.angle_increment;
    float start = msg.angle_min;
    float current = msg.angle_min;
    std::vector<geometry_msgs::PointStamped> currentPoints;
    for(float point : msg.ranges)
    {
        geometry_msgs::PointStamped transformed;
        transformed.header = msg.header;
        transformed.point.z = 0;
        transformed.point.x = point * std::cos(current);
        transformed.point.y = point * std::sin(current);
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
    std::vector<geometry_msgs::PointStamped> currentPoints;
    for(float point : msg.ranges)
    {
        geometry_msgs::PointStamped transformed;
        transformed.header = msg.header;
        transformed.point.z = 0;
        transformed.point.x = point * std::cos(current);
        transformed.point.y = point * std::sin(current);
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
    laserPoints = new std::vector<std::vector<geometry_msgs::PointStamped>>();
    modelPoints = new std::vector<std::vector<geometry_msgs::PointStamped>>();

    long id = 0;
    ros::init(argc, argv, "find_corresponding");
    ros::NodeHandle n;
    ros::Subscriber laserSub = n.subscribe<sensor_msgs::LaserScan>("/scan", 1, laserCallback);
    ros::Subscriber modelSub = n.subscribe<sensor_msgs::LaserScan>("/model", 1, modelCallback);
    ros::Publisher chatter_pub = n.advertise<visualization_msgs::Marker>("corresponding", 0);
    geometry_msgs::PointStamped last;
    while(ros::ok()){
        // get the laser float ranges
        if(laserPoints->size() > 0 && modelPoints->size() > 0){
            std::vector<geometry_msgs::PointStamped> current = laserPoints->front();
            laserPoints->erase(laserPoints->begin());
            std::vector<geometry_msgs::PointStamped> compare = modelPoints->front();
            modelPoints->erase(modelPoints->begin());
            if(id > 0){
                visualization_msgs::Marker cm;
                cm.header.frame_id = last.header.frame_id;
                cm.header.stamp = ros::Time::now();
                cm.action = visualization_msgs::Marker::DELETEALL;
                cm.type = visualization_msgs::Marker::CUBE;
                cm.lifetime = ros::Duration(0.1);
                cm.id = 0;
                chatter_pub.publish(cm);
            }
            while(current.size() > 0){
                geometry_msgs::PointStamped currentPoint = current.front();
                current.erase(current.begin());
                float closestDistance = INFINITY;
                geometry_msgs::Point closestPoint;

                for(geometry_msgs::PointStamped p : compare)
                {
                    float distance = std::sqrt(std::pow(currentPoint.point.x - p.point.x, 2) + std::pow(currentPoint.point.y - p.point.y, 2));
                    if(distance < closestDistance)
                    {
                        closestDistance = distance;
                        closestPoint = p.point;
                    }
                }
                visualization_msgs::Marker marker;
                marker.header.frame_id = currentPoint.header.frame_id;
                marker.header.stamp = ros::Time();
                marker.id = id++;
                marker.type = visualization_msgs::Marker::LINE_STRIP;
                marker.action = visualization_msgs::Marker::ADD;
                marker.lifetime = ros::Duration();
                marker.points.push_back(currentPoint.point);
                marker.points.push_back(closestPoint);

                /*
                float currentPointLength = std::sqrt(std::pow(currentPoint.point.x,2) + std::pow(currentPoint.point.y, 2));
                marker.pose.position.x = currentPoint.point.x / currentPointLength;
                marker.pose.position.y = currentPoint.point.y / currentPointLength;
                marker.pose.position.z = 0.0;
                float closestPointLength = std::sqrt(std::pow(closestPoint.x,2) + std::pow(closestPoint.y, 2));
                marker.pose.orientation.x = closestPoint.x / closestPointLength;
                marker.pose.orientation.y = closestPoint.y / closestPointLength;
                marker.pose.orientation.z = 0.0;
                marker.pose.orientation.w = 1.0;
                */

                marker.color.r = 1.0;
                marker.color.g = 0.0;
                marker.color.b = 0.0;
                marker.color.a = 1.0;
                marker.scale.x = 0.01;
                marker.scale.y = 0.01;
                marker.scale.z = 0.01;
                chatter_pub.publish(marker);
                last = currentPoint;
            }
        }
        ros::spinOnce();
    }
    return 0;
}