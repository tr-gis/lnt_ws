## lnt_ik package description :
This package implements a serivce client used to issue commands to Moveit!. The serivce is defined in the **srv** directory. On running catkin_make from the top of the workspace the necessary headers can be found under *lnt_ws/devel/include/lnt_ik directory*.

The source code is split into lnt_client.cpp and lnt_server.cpp inside **src** directory . The client node listens to data published under topic `/lnt_packet_data`. The topic uses custom message defined under *lnt_ws/src/lnt_packet/msg/lnt_packet.msg*. Based on the packet_code and values[6] array appropriate requests are made to the lnt_server node. Refer to ATP_Manipulator Arm_P1 - Asimov.pdf document for packet code and modes of operation.

## Running the executables :

After running catkin_make command and source the setup file (ie; source catkin_ws/devel/setup.bash ), the executables can be run using the following commands:

`rosrun lnt_ik lnt_client_node`

`rosrun lnt_ik lnt_server_node`
