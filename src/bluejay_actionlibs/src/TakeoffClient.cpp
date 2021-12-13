#include <bluejay_actionlibs/TakeOffAction.h> // Note: "Action" is appended
#include <actionlib/client/simple_action_client.h>

typedef actionlib::SimpleActionClient<bluejay_actionlibs::TakeOffAction> Client;

int main(int argc, char** argv)
{
  ros::init(argc, argv, "do_dishes_client");
  Client client("do_dishes", true); // true -> don't need ros::spin()
  client.waitForServer();
  bluejay_actionlibs::TakeOffGoal goal;
  // Fill in goal here
  
  goal.altitudeGoal = 2;
  goal.velocityTakeoff = 1;
  
  return 0;
}
