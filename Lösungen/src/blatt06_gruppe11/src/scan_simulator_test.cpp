#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Pose.h>
#include <nav_msgs/OccupancyGrid.h>

#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>

#include <mcl_helper/scan_simulator.h>

using namespace mcl_helper;
using namespace message_filters;

class ScanSimulatorTest {
    private:
    ScanSimulator scan_sim;
    ros::NodeHandle nh;
    ros::Publisher scan_simulated;


    public:
    ScanSimulatorTest() : nh() {
        //subscribe
        ros::Subscriber map = nh.subscribe<nav_msgs::OccupancyGrid, const nav_msgs::OccupancyGrid&>("/map", 1000, boost::bind(&ScanSimulatorTest::callback_init, this, _1));
        ros::Subscriber intit_pose = nh.subscribe<geometry_msgs::Pose, const geometry_msgs::Pose&>("/map", 1000, boost::bind(&ScanSimulatorTest::callback_sim, this, _1));

        //publish
        scan_simulated = nh.advertise<sensor_msgs::LaserScan>("/scan_simulated", 1000);
    }

    void callback_init(nav_msgs::OccupancyGrid map_msg) {
        scan_sim.setMap(map_msg);
    
    }

    void callback_sim(const geometry_msgs::Pose& pose_msg) {
        sensor_msgs::LaserScan ls;
        ls.angle_min = -2.3570001125335693;
        ls.angle_max = 2.3570001125335693;
        ls.angle_increment = 0.017459258437156677;
        scan_sim.simulateScan(pose_msg, ls);
        scan_simulated.publish(ls);
    }
};

int main(int argc, char**argv) {
    ros::init(argc, argv, "scan_simulator_test_node");
    ScanSimulatorTest st();
    ros::spin();
    return 0;
}