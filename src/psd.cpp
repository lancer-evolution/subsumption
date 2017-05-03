#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Vector3.h"
#include "sensor_msgs/Range.h"
#include <iostream>

#include "joystick.cpp"

using namespace std;

class psdSub{
public:
  ros::NodeHandle nh;
  ros::Subscriber sub_fl;
  ros::Subscriber sub_ls;
  ros::Subscriber sub_rs;
  ros::Publisher pub;
  float scale;
  float thresh;
  geometry_msgs::Twist twist;
  float msr_fl;

  void flCb(const sensor_msgs::Range::ConstPtr& psd);
  void cmd_pub(geometry_msgs::Twist& tel_twist);
  
  psdSub();
  
};

psdSub::psdSub():
  scale(0.5),
  thresh(0.3)
{
  sub_fl = nh.subscribe("/ardrone/psd/front_left", 10, &psdSub::flCb, this);
  //sub_ls = nh.subscribe("/ardrone/psd/left_side", 10, &psdSub::lsCb, this);
  //sub_rs = nh.subscribe("/ardrone/psd/right_side", 10, &psdSub::rsCb. this);
  pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel",1);
}

void psdSub::flCb(const sensor_msgs::Range::ConstPtr& psd){
  //cout << "fl" << endl;
  msr_fl = psd->range;
  // if(psd->range < 0.3){
  // 	twist.linear.x = -scale*1/psd->range;
  // }else{
  // 	twist.linear.x = 0;
  // }
}
void lsCb(const sensor_msgs::Range::ConstPtr& psd){
  //cout << "ls" << endl;
}
void rsCb(const sensor_msgs::Range::ConstPtr& psd){
  //cout << "rs" << endl;
}
void psdSub::cmd_pub(geometry_msgs::Twist& tel_twist){

  if(msr_fl < thresh){
	twist.linear.x = -scale*1/msr_fl;
	tel_twist.linear.x = twist.linear.x;
  }
  //cout << tel_twist.linear.x << endl;
  pub.publish(tel_twist);
}

int main(int argc, char** argv)
{

  ros::init(argc, argv,"subsumption");
  psdSub psd;
  TeleopArDrone teleop;
  
  ROS_INFO_STREAM("SA started!");
  //ros::spin();
  while(ros::ok()){
	ros::spinOnce();
	psd.cmd_pub(teleop.twist);
  }
  
  return 0;
}
