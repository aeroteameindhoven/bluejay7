#include "bluejay_actionlibs/navigate_server.h"

/*navigate action server(s) communicate with
 * offboard controller through ROS Master
          ------------------------
          --    Task Manager    --
          ------------------------
                    |  |
          ------------------------
          --    Action server   --
          ------------------------
                    |  |
          ------------------------
          --    off_b control   --
          ------------------------
*/

NavigateServer::NavigateServer(){
    ROS_INFO("Nav server is running");
    //Publisher bypasses the goal to OffBoardcontrol node
    goal_pub = nh_.advertise<geometry_msgs::PoseStamped>
        ("/navigateserver/NavigateGoal_To_Controller", 10);

    path_sub = nh_.subscribe<nav_msgs::Path>
        ("/move_base/TrajectoryPlannerROS/global_plan", 10, &NavigateServer::PathCallBack, this);
    goal_sub = nh_.subscribe<geometry_msgs::PoseStamped>
        ("/move_base_simple/goal", 10, &NavigateServer::GoalCallBack, this);

    Init_Parameters();
    ros::Rate frequency(10.0);

    while (ros::ok()){
        if (callback_path == true){
            if(sizeof(global_path.poses) > 0){
                if(global_path.poses[count].pose.position.x == global_goal.pose.position.x &&
                  global_path.poses[count].pose.position.y == global_goal.pose.position.y){
                  ROS_INFO("Goal reached!!");
                }
                else {
                    local_goal.pose.position.x = global_path.poses[count].pose.position.x;
                    local_goal.pose.position.y = global_path.poses[count].pose.position.y;
                    ROS_INFO("Next local goal: x = %f, y = %f", local_goal.pose.position.x, local_goal.pose.position.y);
                    goal_pub.publish(local_goal);
                    count++;
                }
             }
        }
        ros::spinOnce();
        frequency.sleep();
    }
}

NavigateServer::~NavigateServer(void){
}



//callback functions

void NavigateServer::GoalCallBack(const geometry_msgs::PoseStamped::ConstPtr& msg){
    ROS_INFO_ONCE("Position_controller_node got first goal message: x = %f, y = %f", msg->pose.position.x, msg->pose.position.y);
    global_goal = *msg;
}

void NavigateServer::PathCallBack(const nav_msgs::Path::ConstPtr& msg){
    ROS_INFO("Path updated");
    global_path = *msg;
    callback_path = true;
}

void NavigateServer::StateCallback(const mavros_msgs::State::ConstPtr& msg){
  ROS_INFO_ONCE("Navigate_Server got first Command IMU state message.");
  feedback_.arm = msg -> armed;
  current_state = *msg;
  callback_State = true;
}
void NavigateServer::PoseCallback(const geometry_msgs::PoseStamped::ConstPtr& msg) {
    ROS_INFO_ONCE("Navigate_Server received the first altitude.");

    feedback_.pose_x = msg->pose.position.x;
    feedback_.pose_y = msg->pose.position.y;
    feedback_.pose_z = msg->pose.position.z;

    callback_Pose = true;
}


void NavigateServer::Init_Parameters(){
    count = 0;
    callback_Pose = false;
    callback_State = false;
    callback_path = false;
}

int main(int argc, char** argv)
{
   ros::init(argc, argv, "navigate_server");
   new NavigateServer;
   ros::spin();
   return 0;
}
