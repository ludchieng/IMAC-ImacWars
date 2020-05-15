cmake_minimum_required(VERSION 3.7)

project(ImacWars)
add_definitions(-std=c++0x)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FindPkgConfig)

# Source files
set(EXECUTABLE_NAME "imacwars")

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
include_directories(${SDL2_INCLUDE_DIRS})

PKG_SEARCH_MODULE(SDL2_image REQUIRED SDL2_image>=2.0.0)
include_directories(${SDL2IMAGE_INCLUDE_DIRS})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

file(GLOB SRC_FILES
	"src/*.cpp"
	"includes/*.hpp"
)
file(GLOB VENDOR_FILES
	"vendor/FastNoise/*.cpp"
	"vendor/FastNoise/*.hpp"
)

if(SRC_FILES)
    add_executable("${EXECUTABLE_NAME}" ${SRC_FILES} ${VENDOR_FILES}) 
endif(SRC_FILES)
target_link_libraries("${EXECUTABLE_NAME}" ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${OPENGL_LIBRARIES})

# Tests files
#set(TEST_EXECUTABLE_NAME "tests")

#find_package(GTest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIRS})

#file(GLOB TEST_FILES "test/*.cpp")
file(GLOB MAIN_SRC "src/Main.cpp") 
list(REMOVE_ITEM SRC_FILES ${MAIN_SRC}) # Don't include Main.cpp from src

#add_executable("${TEST_EXECUTABLE_NAME}" ${TEST_FILES} ${SRC_FILES} ${VENDOR_FILES})
#target_link_libraries("${TEST_EXECUTABLE_NAME}" ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${OPENGL_LIBRARIES} gtest pthread)

include_directories(BEFORE ".")
include_directories(BEFORE "src/")
