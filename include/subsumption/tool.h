#ifndef _TOOL_H_
#define _TOOL_H_

#include "ros/ros.h"
#include "sensor_msgs/Joy.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Vector3.h"
#include "std_msgs/Empty.h"
#include "std_srvs/Empty.h"
/* #include <opencv2/highgui/highgui.hpp>*/
#include "opencv2/opencv.hpp"

#include <iostream>


using namespace std;

class tool{
 public:
  bool is_flying;
  
  ros::NodeHandle nh_;
  geometry_msgs::Twist twist;
  ros::Publisher pub_takeoff, pub_land, pub_toggle_state, pub_vel;
  //void test();

  tool();
  ~tool();
  void key_event();
  void twist_zero(geometry_msgs::Twist& t);
  char key;
};

 // end namespace

#endif	/* _TOOL_H_ */

