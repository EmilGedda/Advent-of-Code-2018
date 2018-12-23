cmake_minimum_required(VERSION 3.11)
project(AdventOfCode CXX)

file(GLOB_RECURSE srcs CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/day/*/*.cpp")
foreach(file ${srcs})

    # Add target for day
    get_filename_component(problem ${file} NAME_WE)
    get_filename_component(filepath ${file} DIRECTORY)
    get_filename_component(day ${filepath} NAME)
    set(_target "${day}_${problem}")
    add_executable(${_target} ${file} "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
    message(STATUS "Adding solution for day ${day}: ${problem}")
    target_compile_features(${_target} PRIVATE cxx_std_17)
	if(MSVC)
		target_compile_options(${_target} PRIVATE /Ox /Wall -Wextra -pedantic)
	else()
        target_compile_options(${_target} PRIVATE -O2 -Wall -Wextra -pedantic)
	endif()
    target_compile_definitions(${_target} PRIVATE SOLUTION="${_target}")
    target_include_directories(${_target} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

    # Auto run target on input data post build
    #message(STATUS "Adding test: ${_}.txt")
    add_custom_target(${_target}_test
        COMMAND $<TARGET_FILE:${_target}> < "${filepath}/input.txt"
        DEPENDS ${_target})

endforeach()
