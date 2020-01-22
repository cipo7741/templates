cmake_minimum_required(VERSION 3.10)
project(ExampleSwigLuaTable)

set(CMAKE_CXX_STANDARD 11)

option(ENABLE_JEMALLOC "Link against jemalloc if available" ON)
#OPTION(USE_OpenMP "Use OpenMP" ON)
#IF (USE_OpenMP)
#    FIND_PACKAGE(OpenMP)
#    IF (OPENMP_FOUND)
        SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -march=native -Wall -Wextra -ggdb -fno-omit-frame-pointer")
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native -Wall -Wextra -fno-omit-frame-pointer -ggdb")
#    ENDIF ()
#ENDIF ()

FIND_PACKAGE(SWIG REQUIRED)
INCLUDE(${SWIG_USE_FILE})

find_package(Lua 5.3 REQUIRED)
INCLUDE_DIRECTORIES(${LUA_INCLUDE_DIR})
message(STATUS ${LUA_INCLUDE_DIR})

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

SET(CMAKE_SWIG_FLAGS "")

SET_SOURCE_FILES_PROPERTIES(building_construction.i PROPERTIES CPLUSPLUS ON)
SET_SOURCE_FILES_PROPERTIES(building_construction.i PROPERTIES SWIG_FLAGS "-includeall")
SWIG_ADD_LIBRARY(building_construction LANGUAGE lua SOURCES building_construction.i)
SWIG_LINK_LIBRARIES(building_construction ${LUA_LIBRARIES})

add_executable(ExampleSwigLuaTable
        src/main.cpp
        src/Skyscraper.cpp
        src/Skyscraper.hpp
        src/Floor.cpp
        src/Floor.hpp
        building_construction_wrap.cxx)

target_link_libraries(ExampleSwigLuaTable ${LUA_LIBRARIES})