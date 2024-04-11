cmake_minimum_required(VERSION 3.2.0)
project(zamhareer)

file(GLOB_RECURSE src_files "./src/*.cpp")
add_library(${PROJECT_NAME} ${src_files})
target_include_directories(${PROJECT_NAME} PUBLIC "./include")

if(NOT CMAKE_BUILD_TYPE)
  message(STATUS "No build mode is provided so we are builing Debug mode")
  set(CMAKE_BUILD_TYPE "Debug")
endif()


if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
  message(STATUS "Building ${PROJECT_NAME} in debug mode")
  add_compile_definitions("-DDEB_BUILD")
  add_compile_options(-g -Wall)
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
  message(STATUS "Building ${PROJECT_NAME} in release mode")
  add_compile_definitions("-DREL_BUILD")
  add_compile_options("-o3")
endif()

