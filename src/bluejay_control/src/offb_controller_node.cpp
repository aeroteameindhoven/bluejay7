#include "math.h"
#include "offb_controller_node.h"

OffBControllerNode::OffBControllerNode(){
    ROS_INFO("OffBoard mode activated\n");
    ros::ServiceClient arming_client = core.serviceClient<mavros_msgs::CommandBool>("mavros/cmd/arming");
    ros::ServiceClient set_mode_client = core.serviceClient<mavros_msgs::SetMode>("mavros/set_mode");

    //subcriber
    ros::Subscriber state_sub = core.subscribe<mavros_msgs::State>
        ("/mavros/state", 10, &OffBControllerNode::StateCallback, this);
    ros::Subscriber vel_sub = core.subscribe<geometry_msgs::Twist>
        ("/cmd_vel", 10, &OffBControllerNode::VelocityCallback, this);
    ros::Subscriber path_sub = core.subscribe<nav_msgs::Path>
        ("/move_base/TrajectoryPlannerROS/global_plan", 10, &OffBControllerNode::PathCallBack, this);
    ros::Subscriber goal_sub = core.subscribe<geometry_msgs::PoseStamped>
        ("/move_base_simple/goal", 10, &OffBControllerNode::GoalCallBack, this);

    //publisher
    ros::Publisher local_pos_pub = core.advertise<geometry_msgs::PoseStamped>
        ("/mavros/setpoint_position/local", 10);
    ros::Publisher px4_velo_pub = core.advertise<geometry_msgs::TwistStamped>
        ("/mavros/setpoint_velocity/cmd_vel", 10);
    ros::Rate frequency(10.0);

    Init_Parameters();

    ros::Time last_request = ros::Time::now();

    // wait for FCU connection
    while(ros::ok() && !current_state.connected){
        ros::spinOnce();
        frequency.sleep();
    }

    pose.pose.position.x = 0;
    pose.pose.position.y = 0;
    pose.pose.position.z = 0.5;

    //send a few setpoints before starting
    for(int i = 10; ros::ok() && i > 0; --i){
        local_pos_pub.publish(pose);
        ros::spinOnce();
        frequency.sleep();
    }


	ros::Time begin_time = ros::Time::now();
    while(ros::ok() && ((ros::Time::now() - begin_time) < ros::Duration(40))){
            if( current_state.mode != "OFFBOARD" &&
                (ros::Time::now() - last_request > ros::Duration(5.0))){
                if( set_mode_client.call(offb_set_mode) &&
                    offb_set_mode.response.mode_sent){
                    ROS_INFO("Offboard enabled");
                }
                last_request = ros::Time::now();
            } else {
                if( !current_state.armed &&
                    (ros::Time::now() - last_request > ros::Duration(5.0))){
                    if( arming_client.call(arm_cmd) &&
                        arm_cmd.response.success){
                        ROS_INFO("Vehicle armed");
                    }
                    last_request = ros::Time::now();
                }


                if(check_callback == true){
                  if(sizeof(global_path.poses) > 0){
                      if(global_path.poses[count].pose.position.x == global_goal.pose.position.x &&
                        global_path.poses[count].pose.position.y == global_goal.pose.position.y){
                        ROS_INFO("Goal reached!!");
                      } else if(check_goal == true){
                        count = 0;
                        check_goal = false;
                      } else {
                        pose.pose.position.x =  global_path.poses[count].pose.position.x;
                        pose.pose.position.y =  global_path.poses[count].pose.position.y;
                        count++;
                      }
                    }
                  } else {
                      pose.pose.position.z = 0.5;
                  }

                local_pos_pub.publish(pose);

                ros::spinOnce();
                frequency.sleep();
            }
            
            
            
			/*if((ros::Time::now() - begin_time) > ros::Duration(20000.0)) 
			{	ROS_INFO("really?");
				break;
			}
			else {ROS_INFO("Not yet");}*/
        }
        ROS_INFO("exit loop");
}

void OffBControllerNode::GoalCallBack(const geometry_msgs::PoseStamped::ConstPtr& msg){
    ROS_INFO_ONCE("Position_controller_node got first goal message.");
    global_goal = *msg;
    check_goal = true;
}

void OffBControllerNode::PathCallBack(const nav_msgs::Path::ConstPtr& msg){

    global_path = *msg;
    check_callback = true;
}

void OffBControllerNode::StateCallback(const mavros_msgs::State::ConstPtr& msg){
    ROS_INFO_ONCE("Position_controller_node got first Command IMU state message.");
    current_state = *msg;
}

void OffBControllerNode::VelocityCallback(const geometry_msgs::Twist::ConstPtr& vel){
    ROS_INFO_ONCE("offboard_controller_node got first Command Velocity message.");
    cmd_velo = *vel;
}

void OffBControllerNode::DynamicCallback(bluejay_control::ControlConfig &config, uint32_t level){
  ROS_INFO("Altitude request: %f", config.altitude);
}

void OffBControllerNode::Init_Parameters(){
    check_callback = false;
    check_goal = false;
    count = 0;
    offb_set_mode.request.custom_mode = "OFFBOARD";
    arm_cmd.request.value = true;

    pose.pose.position.x = 0;
    pose.pose.position.y = 0;
    pose.pose.position.z = 1;
    f = boost::bind(&OffBControllerNode::DynamicCallback, this, _1, _2);
    server.setCallback(f);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "offboard_node");
    OffBControllerNode *OffBControl = new OffBControllerNode();
    ros::spin();

    return 0;
}
