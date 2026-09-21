cmake_minimum_required(VERSION 3.25)
#[================[subject1: 尝试 CMAKE_MESSAGE_CONTEXT 效果]================]
set(CMAKE_MESSAGE_CONTEXT_SHOW ON CACHE BOOL "Show message context")
list(APPEND CMAKE_MESSAGE_CONTEXT "main")

project(TestApp LANGUAGES CXX)
set(CMAKE_CONFIGURATION_TYPES "Debug;Release;RelWithDebInfo;MinSizeRel" CACHE STRING "" FORCE)

enable_testing()

message("PROJECT_SOURCE_DIR = ${PROJECT_SOURCE_DIR}")
message("CMAKE_SOURCE_DIR = ${CMAKE_SOURCE_DIR}")
message("CMAKE_INSTALL_PREFIX = ${CMAKE_INSTALL_PREFIX}")

message("=== ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt")
# 检测是否为多配置生成器
if(CMAKE_CONFIGURATION_TYPES)
    message(STATUS "")
    message(STATUS "╔══════════════════════════════════════════╗")
    message(STATUS "║  Multi-config Generator Detected         ║")
    message(STATUS "╠══════════════════════════════════════════╣")
    message(STATUS "║ Generator: ${CMAKE_GENERATOR}")
    message(STATUS "║ Configs:   ${CMAKE_CONFIGURATION_TYPES}")
    message(STATUS "╠══════════════════════════════════════════╣")
    message(STATUS "║ Build: cmake --build . --config <Config> ║")
    message(STATUS "╚══════════════════════════════════════════╝")
    message(STATUS "")
else()
    message(STATUS "")
    message(STATUS "╔══════════════════════════════════════════╗")
    message(STATUS "║  Single-config Generator Detected        ║")
    message(STATUS "╠══════════════════════════════════════════╣")
    message(STATUS "║ Generator:  ${CMAKE_GENERATOR}")
    message(STATUS "║ Build Type: ${CMAKE_BUILD_TYPE}")
    message(STATUS "╠══════════════════════════════════════════╣")
    message(STATUS "║ Build: cmake --build .                   ║")
    message(STATUS "╚══════════════════════════════════════════╝")
    message(STATUS "")
endif()

#[================[subject2: 尝试 message(CHECK_START/FAIL/PASS ...) && CMAKE_MESSAGE_INDENT]================]
add_subdirectory(attempts)


add_executable(mainTool
	src/main.cpp
)
add_library(Utils SHARED
	src/utils.cpp
)
target_sources(Utils PUBLIC FILE_SET utils # 3.23+
	TYPE HEADERS
	BASE_DIRS src/include
	FILES
		src/include/utils.hpp
)
target_link_libraries(mainTool PRIVATE Utils)


install(TARGETS mainTool Utils)

add_test(NAME mainToolTest COMMAND mainTool)

add_custom_target(clean_all
	${CMAKE_COMMAND} -E remove_directory ${CMAKE_SOURCE_DIR}/output
	COMMAND ${CMAKE_COMMAND} -E remove_directory ${PROJECT_SOURCE_DIR}/build
	COMMAND ${CMAKE_COMMAND} -E remove_directory ${PROJECT_SOURCE_DIR}/Testing
	COMMENT "Cleaning output directory..."
)

#[[
cmake --preset debug
cmake --build --preset debug-build
cmake --install build --prefix output
]]

#[[
@brief: 尝试 CMAKE_MESSAGE_CONTEXT 效果 -- subject1
        message(CHECK_START/FAIL/PASS ...) && CMAKE_MESSAGE_INDENT -- subject2
@author: liangj.zhang
@date: 2026/09/21

@output:

    [cmake] [main] CMAKE_SOURCE_DIR = D:/Codes/zljgit/kerneltravel/build_tools/cmake/Part_II_Fundamentals/Chapter_14_Debugging_And_Diagnostics/14_1_Log_Messages
    [cmake] [main] CMAKE_INSTALL_PREFIX = C:/Program Files (x86)/TestApp
    [cmake] [main] === D:/Codes/zljgit/kerneltravel/build_tools/cmake/Part_II_Fundamentals/Chapter_14_Debugging_And_Diagnostics/14_1_Log_Messages/CMakeLists.txt
    [cmake] -- [main.attempts] Checking things
    [cmake] -- [main.attempts]   Checking support for something
    [cmake] -- [main.attempts]   Checking support for something - supported
    [cmake] -- [main.attempts]   Checking support for something else
    [cmake] -- [main.attempts]   Checking support for something else - not supported
[cmake] -- [main.attempts] Checking things - ok

@summary: -- subject1
    [main]
    [main.attempts]
    确实会让日志出现的时候，呈现的结构更加清晰

@summary: -- subject2
    subject1 如果说是模块之间的层次更加清晰的话，
    CMAKE_MESSAGE_INDENT 可以让模块内部的层次更加清晰；比如例子中，函数的调用输出 
]]