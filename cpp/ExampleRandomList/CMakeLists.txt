cmake_minimum_required(VERSION 3.7)
project(RandomListExample)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES mainRandomShuffle.cpp mainRandomPop.cpp Timer.h)

find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} )

include_directories( resource )
include_directories( . )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/.. )

add_executable(RandomListExample ${SOURCE_FILES})

target_link_libraries(RandomListExample ${OpenCV_LIBS})