cmake_minimum_required (VERSION 2.6.0)
project (thread_test)

# Needed for threading, as somehow the C++11-threading does not work
# on one of the clusters
FIND_PACKAGE(Boost REQUIRED COMPONENTS thread)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

ADD_EXECUTABLE(thread_test "threadtest.cpp")
TARGET_LINK_LIBRARIES(thread_test ${Boost_LIBRARIES})
