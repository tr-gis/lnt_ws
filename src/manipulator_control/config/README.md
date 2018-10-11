## yaml file descriptions:

**control_loop.yaml**: This file define how often the control loop is to be executed. The control loop consists of reading current
state of motors, updating the necessary controllers and writing a  new value to the motors. The frequency is set by the
`loop_hz` parameter. By default is it set to 5 ie; runs 5 times a second

**manipulator.yaml**: Contains the information required by the dynamixel drivers like Buad Rate, Motor IDs, device path of USB to serial
interface, Joint Names etc.

**manipulator_controller.yaml**: Here controllers are defined. These include individual joint position controllers and a joint trajectory
controller that Moveit! expects. The nardware interface as required by ros_control is also defined here.
