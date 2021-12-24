#include "bluejay_actionlibs/takeoff_server.h"

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

TakeOffServer::TakeOffServer(std::string name) :
  as_(nh_, name, boost::bind(&TakeOffServer::executeCB, this, _1), false),
  action_name_(name)
{
  Init_Parameters();
  pose_sub = nh_.subscribe<geometry_msgs::PoseStamped>
      ("/mavros/local_position/pose", 10, &TakeOffServer::PoseCallback, this);

  //Publisher bypasses the goal to OffBoardcontrol node
  goal_pub = nh_.advertise<bluejay_msgs::TakeOffGoal>
      ("/takeoffserver/TakeOffGoal_To_Controller", 10);
  as_.start();
}

TakeOffServer::~TakeOffServer(void){
}

void TakeOffServer::executeCB(const bluejay_msgs::TakeOffGoalConstPtr &goal)
{
  ROS_INFO("action is being executed");

  ros::Rate frequency(10.0);
  takeoff_goal.TakeoffGoal_x = takeoff_pose.position.x;
  takeoff_goal.TakeoffGoal_y = takeoff_pose.position.y;
  takeoff_goal.TakeoffGoal_z = goal->TakeoffGoal_z;

  goal_pub.publish(takeoff_goal);
  while(ros::ok() && !result_.successTakeoff){
    if (callback_Pose && callback_State) as_.publishFeedback(feedback_);
    if (feedback_.Takeoff_z >= goal->TakeoffGoal_z - 0.1){  //drone reaches the goal
                result_.successTakeoff = true;
                ROS_INFO("TakeOff succeeded");
                as_.setSucceeded(result_);        //set action state to succeeded
    }

    ros::spinOnce();
    frequency.sleep();
  }
}

//callback functions
void TakeOffServer::StateCallback(const mavros_msgs::State::ConstPtr& msg){
  ROS_INFO_ONCE("TakeOff_Server got first Command IMU state message.");
  feedback_.mode = msg -> mode;
  feedback_.arm = msg -> armed;
  current_state = *msg;
  callback_State = true;
}
void TakeOffServer::PoseCallback(const geometry_msgs::PoseStamped::ConstPtr& msg) {
  ROS_INFO_ONCE("TakeOff_Server received the first altitude.");

  takeoff_pose = msg->pose;

  feedback_.Takeoff_x = msg->pose.position.x;
  feedback_.Takeoff_y = msg->pose.position.y;
  feedback_.Takeoff_z = msg->pose.position.z;

  callback_Pose = true;
}

void TakeOffServer::Init_Parameters(){
  callback_Pose = false;
  callback_State = false;
}

int main(int argc, char** argv)
{
   ros::init(argc, argv, "takeoff_server");
   TakeOffServer takeoff_server("takeoff_server");
   ros::spin();
   return 0;
}
