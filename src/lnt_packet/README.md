## lnt_packet package description:

This package is used to publish the desired commands on the `/lnt_packet_data` topic. The command can be published from the 
command line or by editing the src/lnt_publisher.cpp file. The perfered way would from the command line using `rostopic pub` tool.

For complete list of packet_codes and modes of operation refer to ATP_Manipulator Arm_P1 - Asimov.pdf document. 

#### Example :
(Refer to lnt_packet/msg/lnt_packet.msg)
Setting packet_code = 1 and eef_mode = 0 will invoke cartesian control mode where the end effector moves in cartesian co-ordinate 
frame.

#### Publishing values from commandline :

Use `rostopic pub` tool to publish values to the topic from the command line. (Note: make sure the workspace is sourced, the 
lnt_server_node and lnt_client_node should be running for this method to work).

`rostopic pub /lnt_packet_data lnt_packet/lnt_packet "packet_code: 0
values: [0.0, 0.0, 0.0, 0.0, 0.0, 0.0]
eff_mode: 0"`

rostopic supports tabspace completion. So type till `rostopic pub /lnt_packet_data` `<press TAB>` , the rest of the fields will be 
automatically generated. If this does not work, you may have forgot to source the workpace.
