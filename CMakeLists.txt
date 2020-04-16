cmake_minimum_required(VERSION 3.7)

project(ImacWars)
add_definitions(-std=c++0x)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Source files
set(EXECUTABLE_NAME "imacwars")
Set(CMAKE_SHARED_LINKER_FLAGS "-lSDL -lSDL_image -lGLU -lGL -lm")

find_package(SDL REQUIRED)
include_directories(${SDL_INCLUDE_DIRS})

find_package(SDL_image REQUIRED)
include_directories(${SDLIMAGE_INCLUDE_DIRS})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

file(GLOB SRC_FILES "src/*.cpp")

if(SRC_FILES)
    add_executable("${EXECUTABLE_NAME}" ${SRC_FILES}) 
endif(SRC_FILES)
target_link_libraries("${EXECUTABLE_NAME}" ${SDL_LIBRARY} ${SDLIMAGE_LIBRARY} ${OPENGL_LIBRARIES})

# Tests files
set(TEST_EXECUTABLE_NAME "tests")

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

file(GLOB TEST_FILES "test/*.cpp")
file(GLOB MAIN_SRC "src/Main.cpp") 
list(REMOVE_ITEM SRC_FILES ${MAIN_SRC}) # Don't include Main.cpp from src

add_executable("${TEST_EXECUTABLE_NAME}" ${TEST_FILES} ${SRC_FILES})
target_link_libraries("${TEST_EXECUTABLE_NAME}" ${SDL_LIBRARY} ${SDLIMAGE_LIBRARY} ${OPENGL_LIBRARIES} gtest pthread)

include_directories(BEFORE ".")
include_directories(BEFORE "src/")
