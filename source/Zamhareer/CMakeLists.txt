cmake_minimum_required(VERSION 3.0.0)

project(Zamhareer)

message(STATUS "Building the Oditor")


file(GLOB_RECURSE Header_filse ${PROJECT_SOURCE_DIR}/include/*.h)
file(GLOB_RECURSE Source_files ${PROJECT_SOURCE_DIR}/src/*.cpp)


if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	message(STATUS "building ${PROJECT_NAME} in debug mode")
    add_library(${PROJECT_NAME} ${Source_files} ${Header_filse})
	# Adding compiler flags to the my_app target
	target_compile_options(${PROJECT_NAME} PRIVATE
    	-Wall              # Enable all warnings
    	-Wextra            # Enable extra warnings
    	-O2                # Optimization level 2
	)
	# Adding a macro (preprocessor definition) to the target
	target_compile_definitions(${PROJECT_NAME} PRIVATE
    	DEBUG_MODE    # This macro will be defined for target
	)
elseif(${CMAKE_BUILD_TYPE} STREQUAL "_Release")
    message(STATUS "building ${PROJECT_NAME} in Release mode")
	add_library(${PROJECT_NAME} ${Source_files} ${Header_filse})
		# Adding a macro (preprocessor definition) to the target
	target_compile_definitions(${PROJECT_NAME} PRIVATE
		RELEASE_MODE    # This macro will be defined for target
	)
endif()




target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

message(STATUS "adding opengl")
# adding opengl
find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)


# adding glfw
message(STATUS "building glfw")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/vendor/glfw/include)

# adding glad
message(STATUS "building glfw")
add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/glad)
target_link_libraries(${PROJECT_NAME} PRIVATE glad)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/vendor/glad/include)

#adding glm
message(STATUS "building glm")
add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/glm)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/vendor/glm/glm)
target_link_libraries(${PROJECT_NAME} PUBLIC glm)
