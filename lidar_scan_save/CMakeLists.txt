cmake_minimum_required(VERSION 3.8)
project(lidar_save_scans)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(ament_cmake_auto REQUIRED)

ament_auto_find_build_dependencies()

find_package(PCL REQUIRED COMPONENTS)
find_package(pcl_conversions REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)


include_directories(
  ${sensor_msgs_INCLUDE_DIRS}
  include
)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable(lidarSave src/lidar_scan.cpp)

ament_target_dependencies(lidarSave
  rclcpp
  sensor_msgs
  PCL
  pcl_conversions
)

target_link_libraries(lidarSave
  ${PCL_LIBRARIES}
)

install(
 TARGETS lidarSave
 DESTINATION lib/${PROJECT_NAME}
)

ament_export_include_directories(include)
ament_package()