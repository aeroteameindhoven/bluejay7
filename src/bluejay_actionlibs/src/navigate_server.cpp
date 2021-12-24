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

NavigateServer::NavigateServer(std::string name) :
  as_(nh_, name, boost::bind(&NavigateServer::executeCB, this, _1), false),
  action_name_(name)
{
  Init_Parameters();
  pose_sub = nh_.subscribe<geometry_msgs::PoseStamped>
      ("/mavros/local_position/pose", 10, &NavigateServer::PoseCallback, this);

  //Publisher bypasses the goal to OffBoardcontrol node
  goal_pub = nh_.advertise<bluejay_msgs::NavigateGoal>
      ("/navigateserver/NavigateGoal_To_Controller", 10);
  as_.start();
}

NavigateServer::~NavigateServer(void){
}

void NavigateServer::executeCB(const bluejay_msgs::NavigateGoalConstPtr &goal)
{
  ROS_INFO("Navigate action is being executed");

  ros::Rate frequency(10.0);

  goal_pub.publish(goal);
  while(ros::ok() && !result_.successNavigate){
    if (callback_Pose && callback_State) as_.publishFeedback(feedback_);
    if (abs(goal->set_pose_x - feedback_.pose_x) <= 0.1 &&
        abs(goal->set_pose_y - feedback_.pose_y) <= 0.1 &&
        abs(goal->set_pose_z - feedback_.pose_z) <= 0.1){  //drone reaches the goal
                result_.successNavigate = true;
                ROS_INFO("Navigate succeeded");
                as_.setSucceeded(result_);        //set action state to succeeded
    }

    ros::spinOnce();
    frequency.sleep();
  }
}

//callback functions
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
  callback_Pose = false;
  callback_State = false;
}

int main(int argc, char** argv)
{
   ros::init(argc, argv, "navigate_server");
   NavigateServer navigate_server("navigate_server");
   ros::spin();
   return 0;
}
