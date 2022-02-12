#include "bluejay_actionlibs/move_server.h"
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
MoveServer::MoveServer(std::string name) :
    as_(nh_, name, boost::bind(&MoveServer::executeCB, this, _1), false),
    action_name_(name)
{
    Init_Parameters();
    pose_sub = nh_.subscribe<geometry_msgs::PoseStamped>
        ("/mavros/local_position/pose", 10, &MoveServer::PoseCallback, this);

    //Publisher bypasses the goal to OffBoardcontrol node
    goal_pub = nh_.advertise<bluejay_msgs::MoveGoal>
        ("/MoveServer/MoveGoal_To_Controller", 10);
    as_.start();
}

MoveServer::~MoveServer(){
}



void MoveServer::executeCB(const bluejay_msgs::MoveGoalConstPtr &goal)
{
  ROS_INFO("Move action is being executed");

  ros::Rate frequency(10.0);

  while(ros::ok()){

    if (as_.isPreemptRequested()){
                ROS_INFO("%s: Preempted", action_name_.c_str());
                // set the action state to preempted
                as_.setPreempted();
                break;
    }

    if (callback_Pose && callback_State) as_.publishFeedback(feedback_);
    if (abs(Move_pose.position.x - Initial_pose.position.x) > abs(goal->MoveGoal_x)
        && abs(Move_pose.position.y - Initial_pose.position.y) > abs(goal->MoveGoal_y) ){  //drone reaches the goal
                result_.successMove = true;
                ROS_INFO("Move succeeded");
                as_.setSucceeded(result_);        //set action state to succeeded
                break;
    }
    if(goal->MoveGoal_x > 0 && goal->MoveGoal_y > 0){
      Move_goal.MoveGoal_x = Move_pose.position.x + 0.1;
      Move_goal.MoveGoal_y = Move_pose.position.y + 0.1;
      Move_goal.MoveGoal_z = Move_pose.position.z;
      goal_pub.publish(Move_goal);
}
    else if (goal->MoveGoal_x < 0 && goal->MoveGoal_y < 0) {
      Move_goal.MoveGoal_x = Move_pose.position.x - 0.1;
      Move_goal.MoveGoal_y = Move_pose.position.y - 0.1;
      Move_goal.MoveGoal_z = Move_pose.position.z;
      goal_pub.publish(Move_goal);
}
    else if (goal->MoveGoal_x > 0 && goal->MoveGoal_y < 0) {
      Move_goal.MoveGoal_x = Move_pose.position.x + 0.1;
      Move_goal.MoveGoal_y = Move_pose.position.y - 0.1;
      Move_goal.MoveGoal_z = Move_pose.position.z;
      goal_pub.publish(Move_goal);
}
    else if (goal->MoveGoal_x < 0 && goal->MoveGoal_y > 0) {
      Move_goal.MoveGoal_x = Move_pose.position.x - 0.1;
      Move_goal.MoveGoal_y = Move_pose.position.y + 0.1;
      Move_goal.MoveGoal_z = Move_pose.position.z;
      goal_pub.publish(Move_goal);
}
    frequency.sleep();
  }
}


//callback functions
void MoveServer::StateCallback(const mavros_msgs::State::ConstPtr& msg){
    ROS_INFO_ONCE("MoveServer got first Command IMU state message.");
    feedback_.arm = msg -> armed;
    current_state = *msg;
    callback_State = true;
}

void MoveServer::PoseCallback(const geometry_msgs::PoseStamped::ConstPtr& msg) {
    ROS_INFO_ONCE("MoveServer received the first coordinate.");

    Move_pose = msg->pose;

    feedback_.Move_x = msg->pose.position.x;
    feedback_.Move_y = msg->pose.position.y;
    feedback_.Move_z = msg->pose.position.z;
    if (!callback_Pose){
      Initial_pose = msg->pose;
    }
    callback_Pose = true;
}

void MoveServer::Init_Parameters(){
    callback_Pose = false;
    callback_State = false;
    result_.successMove = false;
}

int main(int argc, char** argv)
{
   ros::init(argc, argv, "Move_server");
   MoveServer Move_server("Move_server");
   ros::spin();
   return 0;
}


