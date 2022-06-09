#include "math.h"
#include "bluejay_vision/vision.h"

ArucoNode::ArucoNode(){
	ROS_INFO("Aruco activated\n");
	
	image_sub = core.subscribe<sensor_msgs::Image>
        ("/raspicam_node/image", 10, &ArucoNode::imageCallback, this);
}


void ArucoNode::imageCallback(const sensor_msgs::Image::ConstPtr& msg){
	ROS_INFO_ONCE("width = : %d", msg->width);
	ROS_INFO_ONCE("height = : %d", msg->height);
	

	//preprocess data for blurriness
	
	

	//do marker recognition here	
	
	
	
	//publish position and orientation to landing module
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "vision");
    
	ROS_INFO_ONCE("we are in");
	ArucoNode *test = new ArucoNode();

	ros::spin();
    return 0;
}
