# lnt_ws
*This workspace contains all the source code and executables created by Asimov Robotics while working on the Manipulator Arm project.*

#### _Directory Structure_:

**src** : This directory contains all the source code for the project. The code is grouped into different packages depending on their purpose. Please refer to the README.md files in the respective packages for more details.

**build**: This directory is generated using catkin_make command from the top of this workspace.(ie; from this level).

**devel** :  This directory is generated using catkin_make command from the top of this workspace.(ie; from this level). This directory also contains the executables as described by the CMakeLists.txt file inside the packages. The executables can be found inside devel/lib/package-name. (Note that this is applicable for C++ source code only).

 #### _Code Dependency_:
 
 The code was developed on Ubuntu 14.04 LTS and uses ROS Indigo version.
