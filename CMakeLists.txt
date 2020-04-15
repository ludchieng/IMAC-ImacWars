cmake_minimum_required(VERSION 2.8)

project(ImacWars)


# GENERAL

add_definitions(-std=c++0x)
add_definitions(-Wextra)



# GTEST

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})



# MAIN APP

set(EXECUTABLE_NAME "imacwars")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Source files
file(GLOB SRC_FILES "src/*.cpp")

# Executable dependencies
if(SRC_FILES)
    add_executable("${EXECUTABLE_NAME}" ${SRC_FILES}) 
endif(SRC_FILES)

# Set link libraries
# target_link_libraries($EXECUTABLE_NAME ...)



# TESTS

set(TEST_EXECUTABLE_NAME "tests")

file(GLOB TEST_FILES "test/*.cpp")

# Don't include Main.cpp from src
file(GLOB MAIN_SRC "src/Main.cpp")
list(REMOVE_ITEM SRC_FILES ${MAIN_SRC})

add_executable("${TEST_EXECUTABLE_NAME}" ${TEST_FILES} ${SRC_FILES})

# Set link libs
target_link_libraries("${TEST_EXECUTABLE_NAME}" gtest pthread)

# Include root dir
include_directories(BEFORE ".")
include_directories(BEFORE "src/")
