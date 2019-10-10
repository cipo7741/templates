cmake_minimum_required(VERSION 3.8)
project(ExampleParalell)

set(CMAKE_CXX_STANDARD 14)

OPTION (USE_OpenMP "Use OpenMP" ON)
IF(USE_OpenMP)
    FIND_PACKAGE(OpenMP)
    IF(OPENMP_FOUND)
        SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    ENDIF()
ENDIF()

set(SOURCE_FILES
        main.cpp
        Timer.hpp)

find_package( OpenCV REQUIRED )
find_package(Boost REQUIRED COMPONENTS system chrono thread)

include_directories( ${CMAKE_CURRENT_SOURCE_DIR})
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/.. )
#get_property(inc_dirs DIRECTORY PROPERTY INCLUDE_DIRECTORIES)
#message("inc_dirs = ${inc_dirs}")

add_executable(ExampleParalell ${SOURCE_FILES})

target_link_libraries(ExampleParalell ${OpenCV_LIBS})
target_link_libraries(ExampleParalell ${Boost_LIBRARIES})
#-lpthread -lm -DBOOST_LOG_DYN_LINK -lboost_log -lboost_thread -lpthread)
