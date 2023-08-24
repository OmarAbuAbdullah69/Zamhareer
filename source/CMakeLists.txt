cmake_minimum_required(VERSION 3.0.0)

project(Game)

message(STATUS "Building the app")

file(GLOB_RECURSE Header_filse ${PROJECT_SOURCE_DIR}/Game/include/*.h)
file(GLOB_RECURSE Source_files ${PROJECT_SOURCE_DIR}/Game/src/*.cpp)


if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    add_executable(${PROJECT_NAME} ${Source_files} ${Header_filse})
    target_compile_definitions(${PROJECT_NAME} PRIVATE "Og" "Wall")
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    add_executable(${PROJECT_NAME} ${Source_files} ${Header_filse})
endif()

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/Game/include)

add_subdirectory(${PROJECT_SOURCE_DIR}/Zamhareer)
target_link_libraries(${PROJECT_NAME} PRIVATE Zamhareer)
