#include "bluejay_actionlibs/landing_server.h"
#include "math.h"

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
LandingServer::LandingServer(std::string name) :
  as_(nh_, name, boost::bind(&LandingServer::executeCB, this, _1), false),
  action_name_(name)
{
  Init_Parameters();
  pose_sub = nh_.subscribe<geometry_msgs::PoseStamped>
      ("/mavros/local_position/pose", 10, &LandingServer::PoseCallback, this);

  //Publisher bypasses the goal to OffBoardcontrol node
  goal_pub = nh_.advertise<bluejay_msgs::LandingGoal>
      ("/landingserver/LandingGoal_To_Controller", 10);
  as_.start();
}

LandingServer::~LandingServer(){
}

void LandingServer::executeCB(const bluejay_msgs::LandingGoalConstPtr &goal)
{
  ROS_INFO("Landing action is being executed");

  ros::Rate frequency(10.0);
  landing_goal.LandingGoal_x = landing_pose.position.x;
  landing_goal.LandingGoal_y = landing_pose.position.y;
  landing_goal.LandingGoal_z = goal->LandingGoal_z;
  //landing_goal.mode = "AUTO.LAND";

  goal_pub.publish(landing_goal);
  while(ros::ok() && !result_.successLanding){
    if (as_.isPreemptRequested()){
                ROS_INFO("%s: Preempted", action_name_.c_str());
                // set the action state to preempted
                as_.setPreempted();
                break;
    }
    if (callback_Pose && callback_State) as_.publishFeedback(feedback_);
    if (feedback_.Landing_z - goal->LandingGoal_z <= 0.1){  //drone reaches the goal
                result_.successLanding = true;
                ROS_INFO("Landing succeeded");
                as_.setSucceeded(result_);        //set action state to succeeded
    }

    ros::spinOnce();
    frequency.sleep();
  }
}

//callback functions
void LandingServer::StateCallback(const mavros_msgs::State::ConstPtr& msg){
  ROS_INFO_ONCE("LandingServer got first Command IMU state message.");
  feedback_.arm = msg -> armed;
  current_state = *msg;
  callback_State = true;
}
void LandingServer::PoseCallback(const geometry_msgs::PoseStamped::ConstPtr& msg) {
  ROS_INFO_ONCE("LandingServer received the first altitude.");

  landing_pose = msg->pose;

  feedback_.Landing_x = msg->pose.position.x;
  feedback_.Landing_y = msg->pose.position.y;
  feedback_.Landing_z = msg->pose.position.z;

  callback_Pose = true;
}

void LandingServer::Init_Parameters(){
  callback_Pose = false;
  callback_State = false;
}

int main(int argc, char** argv)
{
   ros::init(argc, argv, "landing_server");
   LandingServer landing_server("landing_server");
   ros::spin();
   return 0;
}
