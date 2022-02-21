#include "bluejay_actionlibs/circle_server.h"
#include <math.h>
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

CircleServer::CircleServer(std::string name) :
    as_(nh_, name, boost::bind(&CircleServer::executeCB, this, _1), false),
    action_name_(name)
{
    Init_Parameters();
    pose_sub = nh_.subscribe<geometry_msgs::PoseStamped>
        ("/mavros/local_position/pose", 10, &CircleServer::PoseCallback, this);

    //Publisher bypasses the goal to OffBoardcontrol node
    goal_pub = nh_.advertise<geometry_msgs::Pose>
        ("/CircleServer/CircleGoal_To_Controller", 10);
    as_.start();
}

CircleServer::~CircleServer(void){
}

void CircleServer::executeCB(const bluejay_msgs::CircleGoalConstPtr &goal){
    // the input from the goal is the circle number, which is float type

    ROS_INFO("Circle action is being executed");
    ros::Rate frequency(10.0);
    //number_of_circles = ;
    radius = 2.0; // circle radius is 2m
    cx = Circle_pose.position.x + radius;
    cy = Circle_pose.position.y; //the coordinates of the center point of circle
    theta = 0.0;

    //Circle_goal.mode = "OFFBOARD";
    

    while(ros::ok()){
        if (as_.isPreemptRequested()){
            ROS_INFO("%s: Preempted", action_name_.c_str());
            // set the action state to preempted
            as_.setPreempted();
            success = false;
            break;
        }

        if (callback_Pose && callback_State) as_.publishFeedback(feedback_);
        Circle_goal.position.x = cx + radius*cos(theta);
        Circle_goal.position.y = cy + radius*sin(theta);
        Circle_goal.position.z = Circle_pose.position.z;
        goal_pub.publish(Circle_goal);
        theta += 0.05;

        if (abs(goal->CircleGoal_num * 2*3.141593 - theta) <= 0.03){
            if(abs(Circle_goal.position.x - Circle_pose.position.x) <= 1 &
            abs(Circle_goal.position.y - Circle_pose.position.y) <= 1){  //drone finishes the circle and reaches the start position
            result_.successCircle = true;
            as_.setSucceeded(result_);
            ROS_INFO("Circle succeeded");
            break;
            //set action state to succeeded
            }
            else{
              result_.successCircle = false;
              as_.setSucceeded(result_);
              ROS_INFO("Way Off the goal! Circle failed!");
              break;
            }
        }

        //ros::spinOnce();
        frequency.sleep();
    }
    ROS_INFO("exiting call back");
}

//callback functions
void CircleServer::StateCallback(const mavros_msgs::State::ConstPtr& msg){
    ROS_INFO_ONCE("Circle_Server got first Command IMU state message.");
    current_state = *msg;
    callback_State = true;
}
void CircleServer::PoseCallback(const geometry_msgs::PoseStamped::ConstPtr& msg) {
    ROS_INFO_ONCE("Circle_Server received the first altitude.");

    Circle_pose = msg->pose;

    feedback_.Circle_x = msg->pose.position.x;
    feedback_.Circle_y = msg->pose.position.y;
    feedback_.Circle_z = msg->pose.position.z;

    callback_Pose = true;
}

void CircleServer::Init_Parameters(){
    callback_Pose = false;
    callback_State = false;
    result_.successCircle = false;
}

int main(int argc, char** argv)
{
   ros::init(argc, argv, "Circle_server");
   CircleServer Circle_server("Circle_server");
   ros::spin();
   return 0;
}
