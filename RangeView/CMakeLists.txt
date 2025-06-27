cmake_minimum_required(VERSION 3.10)
project(RangeView)

set(CMAKE_CXX_STANDARD 14)

find_package(PCL 1.3 REQUIRED)

add_executable(rangeview main.cpp)

target_link_libraries(rangeview ${PCL_LIBRARIES})

