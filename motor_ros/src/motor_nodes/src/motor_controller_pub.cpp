#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>

using namespace std;
int main(int argc, char **argv) {
    ros::init(argc, argv, "Publisher");
    ros::NodeHandle nh;

    

    ros::Publisher state_pub = nh.advertise<std_msgs::String>("motor_controller_publisher", 1000);
    
    while (ros::ok()) {
        std_msgs::String msg;
        int state;

        cout << "Enter a state: foward (1), reverse (2), left (3), right (4), extra speed (5), stop (6). "; 
        cin >> state;
        msg.data = state;

        state_pub.publish(&msg);
    }
    
    ros::spin();
    return 0;
}