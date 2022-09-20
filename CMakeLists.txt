cmake_minimum_required(VERSION 3.19)

project(clientserver)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost 1.75.0 REQUIRED)

add_executable(${PROJECT_NAME} main.cpp helper_functions.cpp)

INCLUDE_DIRECTORIES(${PROJECT_NAME} ${Boost_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})