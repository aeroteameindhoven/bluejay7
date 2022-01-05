#include "bluejay_pathplanner/globalplanner.h"

GlobalPlanner::GlobalPlanner(){
}

int main(int argc, char** argv)
{
   ros::init(argc, argv, "navigation_server");
   GlobalPlanner globalPlanner();
   ros::spin();
   return 0;
}
