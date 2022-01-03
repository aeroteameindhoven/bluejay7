#include "math.h"
#include "bluejay_control/offb_controller_node.h"

OffBControllerNode::OffBControllerNode(){
    ROS_INFO("OffBControllerNode activated\n");
    arming_client = core.serviceClient<mavros_msgs::CommandBool>("mavros/cmd/arming");
    set_mode_client = core.serviceClient<mavros_msgs::SetMode>("mavros/set_mode");

    //subcriber
    state_sub = core.subscribe<mavros_msgs::State>
        ("/mavros/state", 10, &OffBControllerNode::StateCallback, this);
    takeoff_sub = core.subscribe<bluejay_msgs::TakeOffGoal>
        ("/takeoffserver/TakeOffGoal_To_Controller", 10, &OffBControllerNode::TakeOffCallback, this);
    navigate_sub = core.subscribe<geometry_msgs::PoseStamped>
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
            if( current_state.mode != set_mode.request.custom_mode &&
                (ros::Time::now() - last_request > ros::Duration(5.0))){

                if( set_mode_client.call(set_mode) &&
                    set_mode.response.mode_sent){
                    ROS_INFO("%s mode enabled", set_mode.request.custom_mode.c_str());
                }
                last_request = ros::Time::now();

            } else {
               if( current_state.armed != arm_cmd.request.value &&
                    (ros::Time::now() - last_request > ros::Duration(5.0))){

                   if (arm_before){
                       arm_cmd.request.value = false;   //PX4 disarms automatically after landing by AUTO.LAND
                       ROS_INFO("Vehicle auto-disarmed after landing");
                   }
                   else if( arming_client.call(arm_cmd) &&
                        arm_cmd.response.success){

                        if (arm_cmd.request.value) ROS_INFO("Vehicle armed");
                        else ROS_INFO("Vehicle disarmed");

                    }
                    last_request = ros::Time::now();

                }
               mode_before = current_state.mode;
               arm_before = current_state.armed;

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
    set_mode.request.custom_mode = msg->mode;
    arm_cmd.request.value = true;

    ROS_INFO_ONCE("Position_controller_node got the first message from TakeOffGoal: x = %f, y = %f, z = %f", msg->TakeoffGoal_x, msg->TakeoffGoal_y, msg->TakeoffGoal_z);
}

void OffBControllerNode::NavigateCallback(const geometry_msgs::PoseStamped::ConstPtr &msg){
    setPosition.pose.position.x = msg->pose.position.x;
    setPosition.pose.position.y = msg->pose.position.y;

    ROS_INFO_ONCE("Position_controller_node got the first message from NavigateGoal: x = %f, y = %f, z = %f", msg->pose.position.x, msg->pose.position.y, setPosition.pose.position.z);
}

void OffBControllerNode::LandingCallback(const bluejay_msgs::LandingGoal::ConstPtr &msg){
    setPosition.pose.position.x = msg->LandingGoal_x;
    setPosition.pose.position.y = msg->LandingGoal_y;
    setPosition.pose.position.z = msg->LandingGoal_z;
    set_mode.request.custom_mode = msg->mode;

    ROS_INFO_ONCE("Position_controller_node got the first message from LandingGoal: x = %f, y = %f, z = %f", msg->LandingGoal_x, msg->LandingGoal_y, msg->LandingGoal_z);
}

void OffBControllerNode::Init_Parameters(){
    set_mode.request.custom_mode = "AUTO.LOITER";
    arm_cmd.request.value = false;
    arm_before = false;

    setPosition.pose.position.x = 0;
    setPosition.pose.position.y = 0;
    setPosition.pose.position.z = 0;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "offboard_node");
    new OffBControllerNode();
    ros::spin();

    return 0;
}
