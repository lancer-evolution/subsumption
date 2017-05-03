#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Vector3.h"
#include "sensor_msgs/Range.h"
#include <iostream>

#include "joystick.cpp"
#include "subsumption/tool.h"


using namespace std;

class psdSub{
public:
  ros::NodeHandle nh;
  ros::Subscriber sub_fl;
  ros::Subscriber sub_ls;
  ros::Subscriber sub_rs;
  ros::Publisher pub_cmd;
  float scale;
  float thresh;
  geometry_msgs::Twist twist;
  float msr_fl;
  bool back;

  void flCb(const sensor_msgs::Range::ConstPtr& psd);
  void cmd_pub();
  
  psdSub();
  ~psdSub();
  tool tools;
};

psdSub::psdSub():
  scale(1),
  thresh(0.4)
{
  sub_fl = nh.subscribe("/ardrone/psd/front_left", 10, &psdSub::flCb, this);
  //sub_ls = nh.subscribe("/ardrone/psd/left_side", 10, &psdSub::lsCb, this);
  //sub_rs = nh.subscribe("/ardrone/psd/right_side", 10, &psdSub::rsCb. this);
  pub_cmd = nh.advertise<geometry_msgs::Twist>("/cmd_vel",1);
  back = false;
}
psdSub::~psdSub(){
  twist.linear.x = 0;
  twist.angular.z = 0;
  pub_cmd.publish(twist);
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
void psdSub::cmd_pub(){
  //
  if(tools.is_flying){
	if(msr_fl < thresh){		//back
	  twist.linear.x = twist.linear.x - 0.5*(thresh - msr_fl);
	  back = true;

	}else if((msr_fl > thresh) && (back == true)){//yaw
	  twist.linear.x = 0;
	  twist.angular.z = -2;
	  pub_cmd.publish(twist);
	  ros::Duration(0.5).sleep(); // sleep for half a second
	  back = false;
	  //cout << "angular" << endl;
	}else{						//forward
	  twist.linear.x = 1;
	  twist.angular.z = 0;
	}
	//cout << tel_twist.linear.x << endl;
	pub_cmd.publish(twist);
  }
}

int main(int argc, char** argv)
{

  ros::init(argc, argv,"subsumption");
  psdSub psd;
  
  //TeleopArDrone teleop;
  
  ROS_INFO_STREAM("SA started!");
  //ros::spin();
  while(ros::ok()){
	psd.tools.key_event();
	ros::spinOnce();
	psd.cmd_pub();
  }
  
  return 0;
}
