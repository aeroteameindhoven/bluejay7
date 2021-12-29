#include "test_fake_pose.h"


test_fake_pose::test_fake_pose(){
	ROS_INFO("Fake position sensor activated\n");
	ros::Subscriber mavros_odom_sub = core.subscribe<nav_msgs::Odometry>
        ("/mavros/odometry/in", 10, &test_fake_pose::odomCallback, this);
    ros::Subscriber mavros_altitude_sub = core.subscribe<mavros_msgs::Altitude>
        ("/mavros/altitude", 10, &test_fake_pose::altitudeCallback, this);
    ros::Publisher mavros_odom_pub = core.advertise<nav_msgs::Odometry>
    	("/mavros/odometry/out", 10);
    ros::Publisher mocap_pose_pub = core.advertise<geometry_msgs::PoseStamped>
    	("/mavros/vision_pose/pose", 10);
    current_time = ros::Time::now();
    ros::Rate frequency(50.0);
    
    odom_out.header.frame_id = "odom";
    odom_out.child_frame_id = "base_link";
    odom_out.header.stamp = current_time;
    
    mocap.header.frame_id = "map";
    mocap.header.stamp = current_time;
    mocap.pose.orientation.x = 0;
   	mocap.pose.orientation.y = 0;
   	mocap.pose.orientation.z = 0;
    mocap.pose.orientation.w = 1;
    
    while(ros::ok()){
    	ros::spinOnce();
    	current_time = ros::Time::now();
    	mocap_pose_pub.publish(mocap);
    	mavros_odom_pub.publish(odom_out);
        frequency.sleep();
    }
    
}


void test_fake_pose::odomCallback(const nav_msgs::Odometry::ConstPtr& msg){

  // publish odometry msg
	odom_out = *msg;
	odom_out.header.stamp = current_time;
	odom_out.header.frame_id = "odom";
    odom_out.child_frame_id = "base_link";
	//odom_out.x = 0;
	//odom_out.y = 0;
}

void test_fake_pose::altitudeCallback(const mavros_msgs::Altitude::ConstPtr& msg){
	mocap.pose.position.z = msg->local;
	mocap.header.stamp = current_time;
}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "offboard_node");
    test_fake_pose *test = new test_fake_pose();
    ros::spin();

    return 0;
}
