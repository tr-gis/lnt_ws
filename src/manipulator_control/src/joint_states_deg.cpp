#include "ros/ros.h"
#include "sensor_msgs/JointState.h"

/**
 * This tutorial demonstrates simple receipt of messages over the ROS system.
 */

sensor_msgs::JointState joint;

void jCallback(const sensor_msgs::JointState::ConstPtr& msg)
{
  //ROS_INFO("I heard: [%s]", msg->data.c_str());

joint.header = msg->header;
joint.name = msg->name;
joint.velocity = msg->velocity;
joint.effort = msg->effort;
joint.position = msg->position;

for(int i=0;i<msg->position.size();i++){
	joint.position[i]=msg->position[i]*(180/3.14);
}
  //printf("size of position is %d",msg->position.size());

}

int main(int argc, char **argv)
{
  //node name
  ros::init(argc, argv, "joint_state_in_degrees");

  
  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("joint_states", 1000, jCallback);
ros::Publisher joint_pub = n.advertise<sensor_msgs::JointState>("joint_states_in_deg", 1000);

  //publish at the rate of 5 times a second
ros::Rate loop_rate(5);
ROS_INFO("joint_states_in_degrees node is running!");
ROS_INFO("This node subscibes to /joint_states topic published by joint_state_controller/JointStateController");
ROS_INFO("To view output, use command : rostopic echo /joint_states_in_deg");


			

while (ros::ok()){
	//calling ros::spinOnce will invoke callback function and update "joint" variable
	ros::spinOnce();
	joint_pub.publish(joint);
	loop_rate.sleep();
}


  //ros::spin();

  return 0;
}
