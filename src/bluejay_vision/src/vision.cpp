#include "math.h"
#include "bluejay_vision/vision.h"
#include <cv_bridge/cv_bridge.h>


ArucoNode::ArucoNode(){
	ROS_INFO("Aruco activated\n");
	
	cv::Mat inputImage;
	parameters = cv::aruco::DetectorParameters::create();
	dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);

	image_sub = core.subscribe<sensor_msgs::Image>
        ("/raspicam_node/image", 10, &ArucoNode::imageCallback, this);
        
}


void ArucoNode::imageCallback(const sensor_msgs::Image::ConstPtr& msg){
	ROS_INFO_ONCE("width = : %d", msg->width);
	ROS_INFO_ONCE("height = : %d", msg->height);
	
	static const std::string OPENCV_WINDOW = "detected marker window";
	cv::namedWindow(OPENCV_WINDOW);
	//preprocess data for blurriness
	cv::Mat image, imageCopy;
	cv_bridge::CvImagePtr cv_ptr;
    try
    {
      cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    }
    catch (cv_bridge::Exception& e)
    {
		ROS_ERROR("cv_bridge exception: %s", e.what());
		return;
    }
    cv_ptr->image.copyTo(imageCopy);
    //detecting aruco 
    
    ROS_INFO("start detecting");
    std::vector<int> ids;
    std::vector<std::vector<cv::Point2f> > corners;
    cv::aruco::detectMarkers(cv_ptr->image, dictionary, corners, ids);

	ROS_INFO("finish detecting");

	//draw new image 
	if (corners.size() > 1){
		ROS_INFO("uhmmm");
	}
	
    if (ids.size() > 0)
        cv::aruco::drawDetectedMarkers(imageCopy, corners, ids);

	// Update GUI Window
    cv::imshow(OPENCV_WINDOW, imageCopy);
    cv::waitKey(3);
    ROS_INFO("We show the image");
    
    //send coordinate to LAND
    
}



int main(int argc, char **argv)
{
    ros::init(argc, argv, "vision");
    
	ROS_INFO_ONCE("we are in");
	ArucoNode *test = new ArucoNode();

	ros::spin();
    return 0;
}
