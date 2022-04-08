cmake_minimum_required(VERSION 3.21)
project(camel_can_module)

set(CMAKE_CXX_STANDARD 14)

add_executable(test_motor_x8_pro test_motor.cpp)
add_executable(test_basic_cpp test_basic.cpp CanMotorX6.h)
