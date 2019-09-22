cmake_minimum_required(VERSION 3.14)
project(MyList)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(googletest-master/googletest)
include_directories(googletest-master/googletest/include)



set(SOURCE_FILES main.cpp my_list.h)
add_executable(MyList ${SOURCE_FILES})

target_link_libraries(MyList gtest gtest_main)