#include "ros/ros.h"
#include "lnt_ik/lnt_ik.h"
#include <lnt_packet/lnt_packet.h>
#include <stdio.h>


//callback function for subscriber subscribing to the topic /lnt_packet_data
//The packet_code and mode details are taken from topic and used to call corresponding requests to the server
void packet_data_Callback(const lnt_packet::lnt_packet::ConstPtr& packet_data)
{
  //nodehandle for calling service
  ros::NodeHandle n1;
  
  //local variables for storing packet data
  int packet, mode;
  float values[6];
  
  //Decoupling the packet data and storing in local variables for processing
  packet = packet_data->packet_code;
  mode = packet_data->eff_mode;
  for(int i=0;i<6;i++)
  {
	 values[i] = packet_data->values[i];
   }
   
  //Copying the values into service request   
  lnt_ik::lnt_ik srv;
  for(int i=0;i<6;i++)
  {
		 srv.request.values[i] =values[i];
  }

  
  	  
  
  //Checking the packet data and calling the corresponding service
   if(packet == 5)
    {
	 ros::ServiceClient lnt_client1 = n1.serviceClient<lnt_ik::lnt_ik>("joint_space_control_individual");
	 ROS_INFO("Calling joint_space_control_individual service");
	 //call the service 
     if(lnt_client1.call(srv))
     	 ROS_INFO("Client Request success");
     	 else
     	 ROS_INFO("Client Request Failed");
     	 
		 
	}
	
	if(packet == 6)
    {
	 ros::ServiceClient lnt_client1 = n1.serviceClient<lnt_ik::lnt_ik>("joint_space_control_multiple");
	 ROS_INFO("calling joint_space_control_multiple service");
	 //call the service 
     if(lnt_client1.call(srv))
     	 ROS_INFO("Client Request success");
     	 else
     	 ROS_INFO("Client Request Failed");
	}
	
	if(packet == 1 && mode == 0)
    {
	 ros::ServiceClient lnt_client1 = n1.serviceClient<lnt_ik::lnt_ik>("cartesian_space_unconstrained");
	 ROS_INFO("calling cartesian_space_unconstrained service");
	 //call the service 
     if(lnt_client1.call(srv))
     	 ROS_INFO("Client Request success");
     	 else
     	 ROS_INFO("Client Request Failed");
	}
	
	if(packet == 1 && mode == 1)
    {
	 ros::ServiceClient lnt_client1 = n1.serviceClient<lnt_ik::lnt_ik>("cartesian_space_orientation_constraint");
	 ROS_INFO("calling cartesian_space_orientation_constraint service");
	 //call the service 
     if(lnt_client1.call(srv))
     	 ROS_INFO("Client Request success");
     	 else
     	 ROS_INFO("Client Request Failed");
	}
	
	if(packet == 1 && mode == 2)
    {
	 ros::ServiceClient lnt_client1 = n1.serviceClient<lnt_ik::lnt_ik>("cartesian_space_position_constraint");
	 ROS_INFO("calling cartesian_space_position_constraint service");
	 //call the service 
     if(lnt_client1.call(srv))
     	 ROS_INFO("Client Request success");
     	 else
     	 ROS_INFO("Client Request Failed");
	}
	
	if(packet == 2)
    {
	 ros::ServiceClient lnt_client1 = n1.serviceClient<lnt_ik::lnt_ik>("cylindrical_space_control");
	 ROS_INFO("calling cylindrical_space_control service");
	 //call the service 
     if(lnt_client1.call(srv))
     	 ROS_INFO("Client Request success");
     	 else
     	 ROS_INFO("Client Request Failed");
	}
		 
	}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "lnt_manipulator_client");
  ros::NodeHandle n;
  
  //dummy variable for calling home positions service
  lnt_ik::lnt_ik srv;
 
  //Executing the home position command
  ros::ServiceClient lnt_client_home = n.serviceClient<lnt_ik::lnt_ik>("home_position");
  //call the service 
   if(lnt_client_home.call(srv))
     	 ROS_INFO("Home_Client Request success");
   else
     	 ROS_INFO("Home_Client Request Failed");
  
  //Subscriber for packet data
  ros::Subscriber sub1 = n.subscribe("lnt_packet_data", 1000, packet_data_Callback);
    
  ros::spin(); 
  return 0;

 	
  }



