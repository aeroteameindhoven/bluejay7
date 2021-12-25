#include "math.h"
#include "offb_controller_node.h"

OffBControllerNode::OffBControllerNode(){
    ROS_INFO("OffBoard mode activated\n");
    arming_client = core.serviceClient<mavros_msgs::CommandBool>("mavros/cmd/arming");
    set_mode_client = core.serviceClient<mavros_msgs::SetMode>("mavros/set_mode");

    //subcriber
    state_sub = core.subscribe<mavros_msgs::State>
        ("/mavros/state", 10, &OffBControllerNode::StateCallback, this);
    takeoff_sub = core.subscribe<bluejay_msgs::TakeOffGoal>
        ("/takeoffserver/TakeOffGoal_To_Controller", 10, &OffBControllerNode::TakeOffCallback, this);
    navigate_sub = core.subscribe<bluejay_msgs::NavigateGoal>
        ("/navigateserver/NavigateGoal_To_Controller", 10, &OffBControllerNode::NavigateCallback, this);
    landing_sub = core.subscribe<bluejay_msgs::LandingGoal>
        ("/landingserver/LandingGoal_To_Controller", 10, &OffBControllerNode::LandingCallback, this);

    //publisher
    local_pos_pub = core.advertise<geometry_msgs::PoseStamped>
        ("/mavros/setpoint_position/local", 10);
    ros::Rate frequency(10.0);

    Init_Parameters();

    ros::Time last_request = ros::Time::now();

    // wait for FCU connection
    while(ros::ok() && !current_state.connected){
        ros::spinOnce();
        frequency.sleep();
    }

    setPosition.pose.position.x = 0;
    setPosition.pose.position.y = 0;
    setPosition.pose.position.z = 0;

    //send a few setpoints before starting
    for(int i = 10; ros::ok() && i > 0; --i){
        local_pos_pub.publish(setPosition);
        ros::spinOnce();
        frequency.sleep();
    }

    while(ros::ok()){
            if( current_state.mode != "OFFBOARD" &&
                (ros::Time::now() - last_request > ros::Duration(5.0))){
                if( set_mode_client.call(offb_set_mode) &&
                    offb_set_mode.response.mode_sent){
                    ROS_INFO("Offboard enabled");
                }
                last_request = ros::Time::now();
            } else { //disarm before takeoff and after landing
               if( !current_state.armed &&
                    (ros::Time::now() - last_request > ros::Duration(5.0))){
                    if( arming_client.call(arm_cmd) &&
                        arm_cmd.response.success){
                        ROS_INFO("Vehicle armed");
                    }
                    last_request = ros::Time::now();
                }

                  local_pos_pub.publish(setPosition);

                      ros::spinOnce();
                      frequency.sleep();
            }


            }
        ROS_INFO("exit loop");
}

void OffBControllerNode::StateCallback(const mavros_msgs::State::ConstPtr& msg){
    ROS_INFO_ONCE("Position_controller_node got first Command IMU state message.");
    current_state = *msg;
}

void OffBControllerNode::TakeOffCallback(const bluejay_msgs::TakeOffGoal::ConstPtr &msg){
    setPosition.pose.position.x = msg->TakeoffGoal_x;
    setPosition.pose.position.y = msg->TakeoffGoal_y;
    setPosition.pose.position.z = msg->TakeoffGoal_z;
    ROS_INFO_ONCE("Position_controller_node got the first message from TakeOffGoal: x = %f, y = %f, z = %f", msg->TakeoffGoal_x, msg->TakeoffGoal_y, msg->TakeoffGoal_z);
}

void OffBControllerNode::NavigateCallback(const bluejay_msgs::NavigateGoal::ConstPtr &msg){
    setPosition.pose.position.x = msg->set_pose_x;
    setPosition.pose.position.y = msg->set_pose_y;
    setPosition.pose.position.z = msg->set_pose_z;

    ROS_INFO_ONCE("Position_controller_node got the first message from NavigateGoal: x = %f, y = %f, z = %f", msg->set_pose_x, msg->set_pose_y, msg->set_pose_z);
}

void OffBControllerNode::LandingCallback(const bluejay_msgs::LandingGoal::ConstPtr &msg){
    setPosition.pose.position.x = msg->LandingGoal_x;
    setPosition.pose.position.y = msg->LandingGoal_y;
    setPosition.pose.position.z = msg->LandingGoal_z;
    //set_mode_client.call(msg->mode);

    ROS_INFO_ONCE("Position_controller_node got the first message from LandingGoal: x = %f, y = %f, z = %f", msg->LandingGoal_x, msg->LandingGoal_y, msg->LandingGoal_z);
}

void OffBControllerNode::Init_Parameters(){
    offb_set_mode.request.custom_mode = "OFFBOARD";
    arm_cmd.request.value = true;

    setPosition.pose.position.x = 0;
    setPosition.pose.position.y = 0;
    setPosition.pose.position.z = 0;
    server.setCallback(f);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "offboard_node");
    new OffBControllerNode();
    ros::spin();

    return 0;
}
