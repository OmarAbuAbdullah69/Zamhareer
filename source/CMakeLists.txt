cmake_minimum_required(VERSION 3.0.0)

project(Game)

message(STATUS "Building the app")

file(GLOB_RECURSE Header_filse ${PROJECT_SOURCE_DIR}/Game/include/*.h)
file(GLOB_RECURSE Source_files ${PROJECT_SOURCE_DIR}/Game/src/*.cpp)


if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	message(STATUS "building ${PROJECT_NAME} in debug mode")
	add_executable(${PROJECT_NAME} ${Source_files} ${Header_filse})
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
    add_executable(${PROJECT_NAME} ${Source_files} ${Header_filse})
	    # Adding compiler flags to the my_app target
	target_compile_options(${PROJECT_NAME} PRIVATE
    	-Wall              # Enable all warnings
    	-Wextra            # Enable extra warnings
    	-O2                # Optimization level 2
	)	# Adding a macro (preprocessor definition) to the target
	target_compile_definitions(${PROJECT_NAME} PRIVATE
		RELEASE_MODE    # This macro will be defined for target
	)
endif()

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/Game/include)

add_subdirectory(${PROJECT_SOURCE_DIR}/Zamhareer)
target_link_libraries(${PROJECT_NAME} PRIVATE Zamhareer)
