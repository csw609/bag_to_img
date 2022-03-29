cmake_minimum_required(VERSION 3.0.2)
project(bag_to_img)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  roscpp
  std_msgs
)

find_package (OpenCV 3.2.0 REQUIRED)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES bag_to_img
#  CATKIN_DEPENDS cv_bridge roscpp std_msgs
#  DEPENDS system_lib
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(bag_to_img src/bag_to_img)
target_link_libraries(bag_to_img ${catkin_LIBRARIES} ${OpenCV_LIBS})


