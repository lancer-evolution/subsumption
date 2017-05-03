#include "subsumption/tool.h"
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui.h>

using namespace cv;

tool::tool(){
  twist.linear.x = twist.linear.y = twist.linear.z = 1;
  twist.angular.x = twist.angular.y = twist.angular.z = 1;
  
  is_flying = false;
  
  pub_takeoff       = nh_.advertise<std_msgs::Empty>("/ardrone/takeoff",1);
  pub_land          = nh_.advertise<std_msgs::Empty>("/ardrone/land",1);
  pub_toggle_state  = nh_.advertise<std_msgs::Empty>("/ardrone/reset",1);
  pub_vel           = nh_.advertise<geometry_msgs::Twist>("/cmd_vel",1);
  namedWindow("key_controller");
}

tool::~tool(){

}

void tool::key_event(){
  key = cv::waitKey(3);
  
  if(key == 'a'){
	cout << key << endl;
  }
  // fly
  if (!is_flying && ( key == 's' )){
	ROS_INFO("Taking off!");
	pub_takeoff.publish(std_msgs::Empty());
	ros::Duration(1).sleep();
	is_flying = true;
  }
  //land
  if (/*is_flying &&*/ ( key == 'd' )){
  	ROS_INFO("landing");
	twist_zero(twist);
	pub_vel.publish(twist);
  	pub_land.publish(std_msgs::Empty());
  	is_flying = false;
  }
  
}
void tool::twist_zero(geometry_msgs::Twist& t){
  t.linear.x = 0;
  t.linear.y = 0;
  t.linear.z = 0;
  t.angular.x = 0;
  t.angular.y = 0;
  t.angular.z = 0;
}
