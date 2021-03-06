/*************
 
*/

#include "../include/manipulator_control/control_loop.h"
#include "../include/manipulator_control/manipulator_hw_interface.h"

int main(int argc, char** argv)
{
	ros::init(argc, argv, "manipulator_hw");
	ros::NodeHandle nh;

	// NOTE: We run the ROS loop in a separate thread as external calls such
	// as service callbacks to load controllers can block the (main) control loop
	ros::AsyncSpinner spinner(2);
	spinner.start();

	// Create the hardware interface specific to your robot
	boost::shared_ptr<manipulator_control::ManipulatorHWInterface> man_hw_interface (new manipulator_control::ManipulatorHWInterface(nh));
	man_hw_interface->init();

	// Start the control loop
	manipulator_control::HWControlLoop control_loop(nh, man_hw_interface);
	control_loop.run(); // Blocks until shutdown signal recieved

	return 0;
}
