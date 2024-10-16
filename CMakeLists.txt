cmake_minimum_required(VERSION 3.10)

project(GymService)

set(CMAKE_CXX_STANDARD 11)

add_executable(GymService src/Functions.cpp src/main.cpp src/Subscription.cpp src/Place.cpp src/Person.cpp src/User.cpp src/Admin.cpp)

include_directories(headers)
