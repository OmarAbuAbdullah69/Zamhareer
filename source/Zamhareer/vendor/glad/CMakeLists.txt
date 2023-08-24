cmake_minimum_required(VERSION 3.0.0)

project(glad)


add_library(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/src/glad.c ${PROJECT_SOURCE_DIR}/include/glad/glad.h)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
