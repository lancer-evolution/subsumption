cmake_minimum_required(VERSION 2.8.3)
project(subsumption)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  sensor_msgs
  geometry_msgs
  std_srvs
)


catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES subsumption
#  CATKIN_DEPENDS  ardrone_joystick
#  DEPENDS system_lib

)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
# include_directories(include)
include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(psd src/psd.cpp)
target_link_libraries(psd ${catkin_LIBRARIES})
add_executable(psd_auto src/psd_auto.cpp)
target_link_libraries(psd_auto ${catkin_LIBRARIES})
