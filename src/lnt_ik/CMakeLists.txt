cmake_minimum_required(VERSION 2.8.3)
project(lnt_ik)

 ##Compile as C++11, supported in ROS Kinetic and newer
 add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  rospy
  roscpp
  std_msgs
  message_generation
  moveit_ros_planning_interface
  moveit_visual_tools
)
## Generate services in the 'srv' folder
 add_service_files(
    FILES
    lnt_ik.srv
)

## Generate added messages and services with any dependencies listed here
 generate_messages(DEPENDENCIES std_msgs)

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
  #INCLUDE_DIRS include
  #LIBRARIES lnt_ik
  CATKIN_DEPENDS roscpp message_runtime std_msgs
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
include
  ${catkin_INCLUDE_DIRS}
)

## Declare a C++ executables
add_executable(lnt_server_node src/lnt_server.cpp)
##This makes sure the service files are created before buiding binary
add_dependencies(lnt_server_node lnt_ik_gencpp)
target_link_libraries(lnt_server_node ${catkin_LIBRARIES})


## Declare a C++ executables
add_executable(lnt_client_node src/lnt_client.cpp)
##This makes sure the service files are created before buiding binary
add_dependencies(lnt_client_node lnt_ik_gencpp)
target_link_libraries(lnt_client_node ${catkin_LIBRARIES})


