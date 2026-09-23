cmake_minimum_required(VERSION 3.25)

# or command: cmake . --log-context
set(CMAKE_MESSAGE_CONTEXT_SHOW ON CACHE BOOL "Show message context")
list(APPEND CMAKE_MESSAGE_CONTEXT "main")

project(TestApp LANGUAGES CXX)
set(CMAKE_CONFIGURATION_TYPES "Debug;Release;RelWithDebInfo;MinSizeRel" CACHE STRING "" FORCE)

enable_testing()

message(STATUS "PROJECT_SOURCE_DIR = ${PROJECT_SOURCE_DIR}")
message(STATUS "CMAKE_SOURCE_DIR = ${CMAKE_SOURCE_DIR}")
message(STATUS "CMAKE_INSTALL_PREFIX = ${CMAKE_INSTALL_PREFIX}")

message(STATUS "=== ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt")
get_property(isMultiConfig GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
# 检测是否为多配置生成器
if(isMultiConfig)
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
    # set default build type; if set before, there is no influence(cache variable characteristic)
    # avoid 'empty' build type
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type")
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

#[=======================================[]=======================================]

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

#[=======================================[]=======================================]
add_subdirectory(attempts)

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