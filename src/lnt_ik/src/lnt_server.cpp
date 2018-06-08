#include "ros/ros.h"
#include "lnt_ik/lnt_ik.h"

//Moveit header files
#include <moveit/move_group_interface/move_group.h>
#include <moveit/robot_model/robot_model.h>
#include <moveit/robot_state/robot_state.h>
#include <moveit/robot_state/conversions.h>

#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit/planning_scene/planning_scene.h>

#include <moveit_msgs/DisplayRobotState.h>
#include <moveit_msgs/DisplayTrajectory.h>

#include <moveit_msgs/AttachedCollisionObject.h>
#include <moveit_msgs/CollisionObject.h>

//Visulaization tools
#include <moveit_visual_tools/moveit_visual_tools.h>

//For mathematical calculation and conversion
#include <math.h>
#include <Eigen/Geometry>
#include <Eigen/Dense>
#include <cmath>
#include <tf/transform_datatypes.h>

#include <time.h>



class lnt_control
{
 private:
           
	//Variable for storing the planning group which we want
	static constexpr const char* PLANNING_GROUP = "manipulator";  //static cannot be used for string data member and so using char* 
	
	//Pointer object for MoveGroupInterface class
	moveit::planning_interface::MoveGroup *move_group;
	
	//Pointer variable for storing state(position) of joint model group	
	const robot_state::JointModelGroup *joint_model_group;
	
	//Create an object for storing the curret state of the robot
	moveit::core::RobotStatePtr current_state;  
	
	//Temporary variable for copying the joint group positions
	std::vector<double> joint_group_positions;  
	
	//variable for storing safety limits for each joints
	double max[6] = {3.14,3.14,0,2.09,1.57,3.14};
	double min[6] = {-3.14,0,-3.14,-2.09,-1.57,-3.14};
	
		
 public:
 
	double home_pos[6] = {0,45,65,0,-20,0};

        bool deploy_position(lnt_ik::lnt_ik::Request& req,lnt_ik::lnt_ik::Response& res);

	bool home_position(lnt_ik::lnt_ik::Request& req,lnt_ik::lnt_ik::Response& res);
    
    
	bool individual_joint_control(lnt_ik::lnt_ik::Request& req,lnt_ik::lnt_ik::Response& res);
	
	bool multiple_joint_control(lnt_ik::lnt_ik::Request& req,lnt_ik::lnt_ik::Response& res);
	
	bool cartesian_space_unconstrained_control(lnt_ik::lnt_ik::Request& req,lnt_ik::lnt_ik::Response& res);
	
	bool cartesian_space_orientation_constrained_control(lnt_ik::lnt_ik::Request& req,lnt_ik::lnt_ik::Response& res);
	
       	bool cartesian_space_position_constrained_control(lnt_ik::lnt_ik::Request& req,lnt_ik::lnt_ik::Response& res);
	
	bool cylindrical_space_control(lnt_ik::lnt_ik::Request& req,lnt_ik::lnt_ik::Response& res);
	
	bool safety_check(int joint, double position);
	
	float Deg_to_Rad(float angle);
	
	float Rad_to_Deg(float radian);
	
	float Range_conversion(float angle);
	
	lnt_control();
}; 

//Class constructor
lnt_control::lnt_control()
{
	//Invoke the movegroup interface for the planning group which we want
	  move_group = new moveit::planning_interface::MoveGroup(PLANNING_GROUP);
 }
 
//Safety limit check function
bool lnt_control::safety_check(int joint, double position){
	
	if ((position>=min[joint]) && (position<=max[joint]))
		return true;
	else
    		return false;
}

//Degree to radian conversion
float lnt_control::Deg_to_Rad(float angle){
	 angle = (angle *3.14)/180;
	 return angle;
}

//Radian to Degree conversion
float lnt_control::Rad_to_Deg(float radian){
	
	radian = (radian*180)/3.14;
	return radian;
}

//Converting into the range -180 to 180
float lnt_control::Range_conversion(float angle){
	if(angle>180){
		  angle = -(360-angle);}
	else if(angle<-180){
		  angle = 360 + angle;}
	return angle;
}

bool lnt_control::deploy_position(lnt_ik::lnt_ik::Request& req,lnt_ik::lnt_ik::Response& res)
{
	ROS_INFO("Executing deploy position command");	

	ros::NodeHandle home;

	//Sending the manipulator to home position
	//Create a client for multiple joint control

	ros::ServiceClient lnt_client = home.serviceClient<lnt_ik::lnt_ik>("joint_space_control_multiple");
	   
	lnt_ik::lnt_ik srv;
		
	for(int i=0;i<6;i++){
		 srv.request.values[i] = home_pos[i];
	 	}
	 //call the service 
	if(lnt_client.call(srv))
		return true;
	else
        	return false;

}


bool lnt_control::home_position(lnt_ik::lnt_ik::Request& req,lnt_ik::lnt_ik::Response& res)
{
	ROS_INFO("Executing home position command");	

	ros::NodeHandle home;

	//Sending the manipulator to home position
	//Create a client for multiple joint control

	ros::ServiceClient lnt_client = home.serviceClient<lnt_ik::lnt_ik>("joint_space_control_multiple");
	   
	lnt_ik::lnt_ik srv;
		
	for(int i=0;i<6;i++){
		 srv.request.values[i] = 0;
	 	}
	 //call the service 
	if(lnt_client.call(srv))
		return true;
	else
        	return false;

}



bool lnt_control::individual_joint_control(lnt_ik::lnt_ik::Request& req,lnt_ik::lnt_ik::Response& res){

	ROS_INFO("Entering Individual joint space control for : Joint %d ",req.values[0]);

	//Variable for storing the angles in degrees converted to radians 
	float position;
	position = lnt_control::Deg_to_Rad(req.values[1]);
	if(req.values[0]==3){
		position=-position;
	}

	if(lnt_control::safety_check(req.values[0]-1,position)){
	
		 //Store the current state information(position/accleration/velocity) from the movegroup member function
		current_state = move_group->getCurrentState();

		//Get the current position of the joints of the corresponding planning group
		joint_model_group = current_state->getJointModelGroup(PLANNING_GROUP);


		//Copy the positions to another variable for modification.
		current_state->copyJointGroupPositions(joint_model_group, joint_group_positions);

		// Modify the joint state accordingly
		joint_group_positions[req.values[0]-1] = position;  // radians
		move_group->setJointValueTarget(joint_group_positions);

		/*for(int i=0;i<joint_group_positions.size();i++){
			printf("%G \t",joint_group_positions[i]);
		}
		*/
		//Create a plan object(local member) 
		moveit::planning_interface::MoveGroup::Plan my_plan;
		bool success = move_group->plan(my_plan);

		//Execute the plan
		move_group->move(); 
		  
		if (success){
			ROS_INFO("Joint : %d moved to goal : %f",req.values[0],req.values[1]);
			return true;
			}
		else{
		   ROS_INFO("Individual joint space goal failed for Joint : %d",req.values[0]);
			return false;
			}
		}
	else{
		ROS_INFO("Exceeding joint limits for Joint : %d",req.values[0]);
		return false;
		}
}

bool lnt_control::multiple_joint_control(lnt_ik::lnt_ik::Request& req,lnt_ik::lnt_ik::Response& res){
	
	ROS_INFO("Entering Multiple joint space control");

	//Variable for storing the angles in degrees converted to radians for multiple joints 
	float multiple_joint_position[6];

	//Store the current state information(position/accleration/velocity) from the movegroup member function
	current_state = move_group->getCurrentState();

	sleep(5);

	//Get the current position of the joints of the corresponding planning group
	joint_model_group = current_state->getJointModelGroup(PLANNING_GROUP);

	//Copy the positions to another variable for modification.
	current_state->copyJointGroupPositions(joint_model_group, joint_group_positions);

	//Modify the joint state accordingly
	for(int i=0;i<6;i++){
		//Degree to radians conversion
		if(i==2){
		multiple_joint_position[i] = -lnt_control::Deg_to_Rad(req.values[i]);}
		else{
		multiple_joint_position[i] = lnt_control::Deg_to_Rad(req.values[i]);}

		//Checking the limits
		if(safety_check(i,multiple_joint_position[i])){	  
			joint_group_positions[i] = multiple_joint_position[i];	   		}
	   	else{
		   ROS_INFO(" Joint %d out of range",i) ;}
		}  

	move_group->setJointValueTarget(joint_group_positions);

	//Create a plan object(local member) 
	moveit::planning_interface::MoveGroup::Plan my_plan;
	bool success = move_group->plan(my_plan);

	//Execute the plan
	move_group->move(); 

	if (success){
		ROS_INFO("Executed Multiple joint space goal successfully");
		return true;}
       else{
		ROS_INFO("Executing Multiple joint space goal failed");
		return false;}
	
}

bool lnt_control::cartesian_space_unconstrained_control(lnt_ik::lnt_ik::Request& req,lnt_ik::lnt_ik::Response& res){
	

	//!!!Note : This service is not part of ATP requirement. It was developed for debugging purposes.
	ROS_INFO("Entering Cartesian space uncontrained control");

	//Create local variables for assigning the packet data
	float x,y,z,alpha,beta,gama;

	//Variable for storing plan status
	bool success;

	//Assign the values from the client request data
	x=req.values[0];
	y=req.values[1];
	z=req.values[2];
	alpha=req.values[3];
	beta=req.values[4];
	gama=req.values[5];


	//Creating a local variable for storing the start_pose
	geometry_msgs::Pose start_pose;

	//Get the current pose
	geometry_msgs::PoseStamped current_pose = move_group->getCurrentPose();

	//Copy the current pose to start pose evariable
	start_pose.position.x = current_pose.pose.position.x;
	start_pose.position.y = current_pose.pose.position.y;
	start_pose.position.z = current_pose.pose.position.z; 
	start_pose.orientation.x =  current_pose.pose.orientation.x;
	start_pose.orientation.y = current_pose.pose.orientation.y;
	start_pose.orientation.z = current_pose.pose.orientation.z;
	start_pose.orientation.w = current_pose.pose.orientation.w;

	
	//Create a quaternion to assign the start pose orientation 
	tf::Quaternion q1(start_pose.orientation.x,start_pose.orientation.y,start_pose.orientation.z,start_pose.orientation.w);
		  
	//Convert the quaternion into Euler angles 		 
	tf::Matrix3x3 m(q1);
	double roll, pitch, yaw;
	m.getRPY(roll, pitch, yaw);
    
	//Increment the angles from the packet data 
	alpha = alpha +roll;
	beta = beta+ pitch;
	gama = gama +yaw;
    
	//Create a quaternion for assigning final orientation 
	tf::Quaternion q2;
	q2 = tf::createQuaternionFromRPY(alpha, beta, gama);

	//Apply the corresponding incrementation
	geometry_msgs::Pose target_pose;
	target_pose.position.x = start_pose.position.x+x;
	target_pose.position.y = start_pose.position.y+y;
	target_pose.position.z =   start_pose.position.z+z; 
	target_pose.orientation.x =  q2.x();
	target_pose.orientation.y = q2.y();
	target_pose.orientation.z = q2.z();
	target_pose.orientation.w =  q2.w();
      
	//Create a plan object
	moveit::planning_interface::MoveGroup::Plan my_plan;

	//Set the target pose
	move_group->setPoseTarget(target_pose);
	move_group->setPlanningTime(5.0);

	//Finding the plan status		
	success = move_group->plan(my_plan);

	//Execute the plan
	move_group->move(); 

	if (success){
		ROS_INFO("Executed cartesian space unconstrained goal successfully");
		return true;}
	else{
	   	ROS_INFO("Executing cartesian space unconstrained goal failed");
		return false;}
}

bool lnt_control::cartesian_space_orientation_constrained_control(lnt_ik::lnt_ik::Request& req,lnt_ik::lnt_ik::Response& res)
{
	ROS_INFO("Entering Cartesian space - constant orientation control");
	
	//Create local variables for assigning the packet data
	float x,y,z,alpha,beta,gama;
	
	//Variable for storing plan status
	bool success;
	
	//Assign the values from the client request data
	x=req.values[0];
	y=req.values[1];
	z=req.values[2];
	alpha=req.values[3];
	beta=req.values[4];
	gama=req.values[5];
		
	//Creating a local variable for storing the start_pose
	geometry_msgs::Pose start_pose;
	
	//Get the current pose
	geometry_msgs::PoseStamped current_pose = move_group->getCurrentPose();
	
	//Copy the current pose to start pose evariable
	start_pose.position.x = current_pose.pose.position.x;
	start_pose.position.y = current_pose.pose.position.y;
	start_pose.position.z = current_pose.pose.position.z; 
	start_pose.orientation.x =  current_pose.pose.orientation.x;
	start_pose.orientation.y = current_pose.pose.orientation.y;
	start_pose.orientation.z = current_pose.pose.orientation.z;
	start_pose.orientation.w = current_pose.pose.orientation.w;

	ROS_INFO("Cartesian parameters before executing goal \npos.x : %f \tpos.y : %f \tpos.z : %f",current_pose.pose.position.x,current_pose.pose.position.y,current_pose.pose.position.z);
	ROS_INFO("\nori.x : %f \tori.y : %f \tori.z : %f \tori.w : %f",current_pose.pose.orientation.x,current_pose.pose.orientation.y,current_pose.pose.orientation.z,current_pose.pose.orientation.w);
	
	//Planning with orientation Constraints
	moveit_msgs::OrientationConstraint ocm;
	ocm.link_name = "lnt_gripper_tool_frame";
	ocm.header.frame_id = "base_link";
	ocm.orientation.x =  start_pose.orientation.x;
	ocm.orientation.y = start_pose.orientation.y;
	ocm.orientation.z = start_pose.orientation.z;
	ocm.orientation.w =  start_pose.orientation.w;
	ocm.absolute_x_axis_tolerance = 0.1;
	ocm.absolute_y_axis_tolerance = 0.1;
	ocm.absolute_z_axis_tolerance = 0.1;
	ocm.weight = 0.5;

	//Now, set it as the path constraint for the group.
	moveit_msgs::Constraints test_constraints;
	test_constraints.orientation_constraints.push_back(ocm);
	move_group->setPathConstraints(test_constraints);
	
	//Assign the target pose
	geometry_msgs::Pose target_pose;
	target_pose.position.x =   start_pose.position.x+x; 
	target_pose.position.y =   start_pose.position.y+y;
	target_pose.position.z =   start_pose.position.z+z; 
	target_pose.orientation.x =  start_pose.orientation.x;
	target_pose.orientation.y = start_pose.orientation.y;
	target_pose.orientation.z = start_pose.orientation.z;
	target_pose.orientation.w = start_pose.orientation.w; 

	//Create a plan object
	moveit::planning_interface::MoveGroup::Plan my_plan;

	//Set the target
	move_group->setPoseTarget(target_pose);
	move_group->setPlanningTime(5.0);
	
	//Finding the plan status		
	success = move_group->plan(my_plan);

	//Executing the plan
	move_group->move(); 
	  
	// Clearing path constraint
	move_group->clearPathConstraints();

	if (success){
		ROS_INFO("Cartesian space - constant orientation goal executed successfully");
		current_pose = move_group->getCurrentPose();
		ROS_INFO("New Cartesian parameters \npos.x : %f \tpos.y : %f \tpos.z : %f",current_pose.pose.position.x,current_pose.pose.position.y,current_pose.pose.position.z);
	ROS_INFO("\nori.x : %f \tori.y : %f \tori.z : %f \tori.w : %f",current_pose.pose.orientation.x,current_pose.pose.orientation.y,current_pose.pose.orientation.z,current_pose.pose.orientation.w);
		return true;}
	else{
		ROS_INFO("Executing cartesian space orientation constrained goal failed");
		return false;}
	
}

bool lnt_control::cartesian_space_position_constrained_control(lnt_ik::lnt_ik::Request& req,lnt_ik::lnt_ik::Response& res)
{
	
	ROS_INFO("Entering Cartesian space position control");
	
	//Create local variables for assigning the packet data
	float x,y,z,alpha,beta,gama;
	
	//Variable for storing plan status
	bool success;
	
	//Assign the values from the client request data
	x=req.values[0];
	y=req.values[1];
	z=req.values[2];
	alpha=req.values[3];
	beta=req.values[4];
	gama=req.values[5];
	
	
	//Creating a local variable for storing the start_pose
	geometry_msgs::Pose start_pose;
	
	//Get the current pose
	geometry_msgs::PoseStamped current_pose = move_group->getCurrentPose();
	
	//Copy the current pose to start pose evariable
	start_pose.position.x = current_pose.pose.position.x;
	start_pose.position.y = current_pose.pose.position.y;
	start_pose.position.z = current_pose.pose.position.z; 
	start_pose.orientation.x =  current_pose.pose.orientation.x;
	start_pose.orientation.y = current_pose.pose.orientation.y;
	start_pose.orientation.z = current_pose.pose.orientation.z;
	start_pose.orientation.w = current_pose.pose.orientation.w;

	ROS_INFO("Orientation before executing goal \nori.x: %f \tori.y: %f \tori.z: %f \tori.w: %f",current_pose.pose.orientation.x,current_pose.pose.orientation.y,current_pose.pose.orientation.z,current_pose.pose.orientation.w);

	//Create a quaternion to assign the start pose orientation 
	tf::Quaternion q1(start_pose.orientation.x,start_pose.orientation.y,start_pose.orientation.z,start_pose.orientation.w);
		  
	//Convert the quaternion into Euler angles 		 
	tf::Matrix3x3 m(q1);
	double roll, pitch, yaw;
	m.getRPY(roll, pitch, yaw);

	//Increment the angles from the packet data 
	alpha = alpha +roll;
	beta = beta+ pitch;
	gama = gama +yaw;

	//Create a quaternion for assigning final orientation 
	tf::Quaternion q2;
	q2 = tf::createQuaternionFromRPY(alpha, beta, gama);

	//Create  Position constraints
	moveit_msgs::PositionConstraint pcm;
	pcm.link_name = "lnt_gripper_tool_frame";
	pcm.header.frame_id = "base_link";
	pcm.target_point_offset.x = start_pose.position.x;
	pcm.target_point_offset.y =  start_pose.position.y;
	pcm.target_point_offset.z =  start_pose.position.z; 
	pcm.weight = 0.9;

	//Set the constraint
	moveit_msgs::Constraints pos_constraints;
	pos_constraints.position_constraints.push_back(pcm);
	move_group->setPathConstraints(pos_constraints);

	//set the target pose
	geometry_msgs::Pose target_pose;
	target_pose.position.x = start_pose.position.x;
	target_pose.position.y = start_pose.position.y;
	target_pose.position.z =   start_pose.position.z; 
	target_pose.orientation.x =  q2.x();
	target_pose.orientation.y = q2.y();
	target_pose.orientation.z = q2.z();
	target_pose.orientation.w = q2.w();
	 
	//Creating a plan object
	moveit::planning_interface::MoveGroup::Plan my_plan;
	  
	//Set the target pose  
	move_group->setPoseTarget(target_pose);
	move_group->setPlanningTime(5.0);

	//Plan to the corresponding setpose target
	success = move_group->plan(my_plan);

	//Execute the plan
	move_group->move(); 

	if (success){
		ROS_INFO("Executed cartesian space position constrained goal successfully");
		current_pose = move_group->getCurrentPose();

		ROS_INFO("Orientation after executing goal \n ori.x: %f \tori.y: %f \tori.z: %f \tori.w: %f",current_pose.pose.orientation.x,current_pose.pose.orientation.y,current_pose.pose.orientation.z,current_pose.pose.orientation.w);
		return true;}
	else{
		ROS_INFO("Executing cartesian space position constrained goal failed");
		return false;}
}

bool lnt_control::cylindrical_space_control(lnt_ik::lnt_ik::Request& req,lnt_ik::lnt_ik::Response& res)
{
	ROS_INFO("Entering cylindrical space control");

	//Create local variables for assigning the packet data
	double r,theta,z;

	//Variable for storing plan status
	bool success;

	//Assign the values from the client request data
	r=req.values[0];
	theta=req.values[1];
	z=req.values[2];

	//For theta only control mode
	if( theta != 0 && r == 0 && z==0){
    
		//Store the current state information(position/accleration/velocity) from the movegroup member function
		current_state = move_group->getCurrentState();

		//Get the current position of the joints of the corresponding planning group
		joint_model_group = current_state->getJointModelGroup(PLANNING_GROUP);

		//Copy the positions to another variable for modification.
		current_state->copyJointGroupPositions(joint_model_group, joint_group_positions);

		//Adding the theta incrementation with current theta   
		theta = theta + lnt_control::Rad_to_Deg(joint_group_positions[0]);

		//Convering within +180 to -180 range
		theta = lnt_control::Range_conversion(theta);

		//Creating a client for individual joint control    
		ros::NodeHandle n1;
		ros::ServiceClient lnt_client_joint = n1.serviceClient<lnt_ik::lnt_ik>("joint_space_control_individual");

		//Assigning the theta to base joint
		lnt_ik::lnt_ik srv;
		srv.request.values[0]=1;
		srv.request.values[1]=theta;
                //ROS_INFO
		//Calling the service 
		if(lnt_client_joint.call(srv)){
			ROS_INFO("Executed cylindrical space goal successfully");
			return true;}
		else{
			ROS_INFO("Executing cylindrical space goal failed");
			return false;}
		}
   
	else{
		//Variable for storing the coordinates of end effector
		float x1,y1;
		 
		//variable for storing the extension length of the end effector
		float R;
		 
		//Variable for storing the initial theta of end effector
		float theta1;
		 
		//Get the current pose
		geometry_msgs::PoseStamped current_pose = move_group->getCurrentPose();
		ROS_INFO("current pose ");

		//Assign the current pose x,y coordinates to local variables
		x1 = current_pose.pose.position.x;
		y1 = current_pose.pose.position.y;
		 
		//Finding the extension of the arm 
		R = sqrt(pow(x1,2)+pow(y1,2));

		//Adding the initial extension of the arm with required additional movement from client data
		R = R+r;

		//Calculating the initial theta in radian
		theta1 = atan(y1/x1);

		//Finding the final theta angle
		theta = theta + lnt_control::Rad_to_Deg(theta1);

		//Converting within +180 to -180 range
		theta = lnt_control::Range_conversion(theta);

		//Converting to radian
		theta = lnt_control::Deg_to_Rad(theta);
		       
		//Cylindrical to cartesian conversion
		x1= R*cos(theta);
		y1= R*sin(theta);

		//Finding the incrementation values in x and y direction
		//Reason for subtracting the current position is that ,only incrementation values should be sent to the service but the x1,y1 we have is final target position
		x1 = x1-current_pose.pose.position.x;;
		y1 = y1-current_pose.pose.position.y;


		//Creating a client for cartesian space orientation constrained control    
		ros::NodeHandle n1;
		ros::ServiceClient lnt_client_cartesian_orientation_control = n1.serviceClient<lnt_ik::lnt_ik>("cartesian_space_orientation_constraint");

		//Sending the incrementation values 
		lnt_ik::lnt_ik srv;
		srv.request.values[0]=x1;  
		srv.request.values[1]=y1;
		srv.request.values[2]=z;

		//Calling the service 
		if(lnt_client_cartesian_orientation_control.call(srv)){
			ROS_INFO("Executed cylindrical space goal successfully");
    			return true;
    			}
		else{
	  		ROS_INFO("Executing cylindrical space goal failed");
	  		return false;
			}
	}
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "lnt_manipulator_server");
	ros::NodeHandle n;

    
    //Creating an object of the class
	lnt_control arm;
        
	ros::ServiceServer service1 =  n.advertiseService("joint_space_control_individual", &lnt_control::individual_joint_control, &arm);
	ros::ServiceServer service2 =  n.advertiseService("joint_space_control_multiple", &lnt_control::multiple_joint_control, &arm);
	ros::ServiceServer service3 =  n.advertiseService("cartesian_space_unconstrained", &lnt_control::cartesian_space_unconstrained_control, &arm);
	ros::ServiceServer service4 =  n.advertiseService("cartesian_space_orientation_constraint", &lnt_control::cartesian_space_orientation_constrained_control, &arm);
	ros::ServiceServer service5 =  n.advertiseService("cartesian_space_position_constraint", &lnt_control::cartesian_space_position_constrained_control, &arm);
	ros::ServiceServer service6 =  n.advertiseService("cylindrical_space_control", &lnt_control::cylindrical_space_control, &arm);
        ros::ServiceServer service7 =  n.advertiseService("deploy_position", &lnt_control::deploy_position, &arm);
	ros::ServiceServer service8 =  n.advertiseService("home_position", &lnt_control::home_position, &arm);
		

	ros::AsyncSpinner spinner(3);
  	spinner.start();
  	
  	
   	 
	
	ros::waitForShutdown();
	return 0;
}

