cmake_minimum_required(VERSION 3.8)
project(ExampleCellOverlap)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp Cell.cpp Cell.hpp Grid.cpp Grid.hpp Shape.cpp Shape.hpp)


find_package( OpenCV REQUIRED )
find_package(Boost REQUIRED COMPONENTS system chrono thread)

include_directories( ${Boost_INCLUDE_DIRS} )
include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR})
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/.. )

#get_property(inc_dirs DIRECTORY PROPERTY INCLUDE_DIRECTORIES)
#message("inc_dirs = ${inc_dirs}")

add_executable(ExampleCellOverlap ${SOURCE_FILES})

target_link_libraries(ExampleCellOverlap ${OpenCV_LIBS})
target_link_libraries(ExampleCellOverlap ${Boost_LIBRARIES})
#-lpthread -lm -DBOOST_LOG_DYN_LINK -lboost_log -lboost_thread -lpthread)
