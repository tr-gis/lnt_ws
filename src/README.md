## Package Description:

1. **lnt_ik**: This package contains the serivce-client architecture, which is used to give desired commands to the Manipulator Arm.
Refer to ATP_Manipulator Arm_P1 - Asimov.pdf for mode information. Further documentation is available inside package.

2. **lnt_moveit_config** : This package is genereated using Moveit! Setup Assistant. It contains the srdf and moveit configuration necessary to control and visualize the robot from Rviz.

3. **lnt_packet** : This package describes the message and code used to command values to the robot. Refer to ATP_Manipulator Arm_P1 - Asimov.pdf for mode information. Further documentation is available inside package.

4.**lnt_urdf_description** : This package holds the corrected urdf created by Asimov Robotics.

5. **manipulator_control** : This package contains the driver level code ,ros control hardware interface required to operate the manipulator with Moveit!.
