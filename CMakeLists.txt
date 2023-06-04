cmake_minimum_required(VERSION 3.10.2)
project(imu_interface)

add_executable(imu_interface src/i2c_driver.cpp src/imu_interface.cpp)
target_include_directories(imu_interface PUBLIC include)
