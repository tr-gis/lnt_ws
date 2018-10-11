## manipulator_control package description:

This package forms the core of the workspace. This is where motor specifications, dynamixel driver code and hardware interface 
are defined.

**config** : Contains the .yaml files with parameters to be loaded into the parameter server.

**include** : All the header files are defined here

**launch** : Contains all the necessary launch file to run the executables and to load the .yaml files into the parameter server.

**src** : Contains all the source code.

#### Running the package:

1. launch manipulator.launch file : `roslaunch manipulator_control manipulator.launch`


Make sure device path, motors IDs, baud rate are set correctly in the .yaml files.


2. run the main hardware node : `rosrun manipulator_control man_hw`

Now you can issue command to the manipulator. Refer to lnt_packet packge for more information on this.
