The following files are part of Dynamixel SDK. They define the basic functionality for interfacing with Dynamixel servos.

- group_bulk_read.cpp
- group_bulk_write.cpp
- group_sync_read.cpp
- group_sync_write.cpp
- packet_handler.cpp
- port_handler.cpp
- port_handler_arduino.cpp
- port_handler_linux.cpp
- port_handler_mac.cpp
- port_handler_windows.cpp
- protocol1_packet_handler.cpp
- protocol2_packet_handler.cpp`

**dxl_driver.cpp** : This file contains code that connects to the servos as defined in the manipulator.yaml file. It reads and writes position values to
the servos. Refer to code comments for more description.

**man_hw_main.cpp**: This file contains code that initialises the hardware interface and starts the control loop.

**joint_states_deg.cpp**: This file contains code that converts to joint angles from radians ( as published by driver) into degress.

**manipulator_hw_interface.cpp** : The ros_control hardware interface is implemented here. For more details refer to ros_control 
package.

**control_loop.cpp** : Contains the code for control loop.
