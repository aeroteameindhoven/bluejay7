#include "math.h"
#include "bluejay_vision/vision.h"

ArucoNode::ArucoNode(){
	ROS_INFO("Aruco activated\n");
	
	cv::Mat inputImage;
	
	std::vector<int> markerIds;
	std::vector<std::vector<cv::Point2f>> markerCorners, rejectedCandidates;
	parameters = cv::aruco::DetectorParameters::create();
	dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);

	image_sub = core.subscribe<sensor_msgs::Image>
        ("/raspicam_node/image", 10, &ArucoNode::imageCallback, this);
        
        
}


void ArucoNode::imageCallback(const sensor_msgs::Image::ConstPtr& msg){
	ROS_INFO_ONCE("width = : %d", msg->width);
	ROS_INFO_ONCE("height = : %d", msg->height);
	
	//preprocess data for blurriness
	cv::Mat image, imageCopy;
	

	//do marker recognition here	
	std::vector<int> ids;
    std::vector<std::vector<cv::Point2f> > corners;
    cv::aruco::detectMarkers(image, dictionary, corners, ids);
    // if at least one marker detected
    if (ids.size() > 0)
        cv::aruco::drawDetectedMarkers(imageCopy, corners, ids);
    
	
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
