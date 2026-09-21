cmake_minimum_required(VERSION 3.25)

# or command: cmake . --log-context
set(CMAKE_MESSAGE_CONTEXT_SHOW ON CACHE BOOL "Show message context")
list(APPEND CMAKE_MESSAGE_CONTEXT "main")
set(CMAKE_MESSAGE_LOG_LEVEL DEBUG)

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

#[========================[subject1: 14.5 节调试生成器表达式的例子]========================]
set(incDirs $<TARGET_PROPERTY:mainTool,INCLUDE_DIRECTORIES>)
set(genex "-I$<JOIN:${incDirs},-I>")
file(GENERATE 
    OUTPUT "${CMAKE_BINARY_DIR}/genex_output.txt" 
    CONTENT "incDirs = ${incDirs}\ngenex = ${genex}\n"
)
#[========================[subject1: 14.5 节调试生成器表达式的例子]========================]

#[========================[subject2: 21.3 不仅OUTPUT使用生成器，内容也嵌入生成器表达式]========================]
file(GENERATE
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/details-$<CONFIG>.txt
    CONTENT [[
Built as "$<CONFIG>" for platform "$<PLATFORM_ID>".
Defines: $<TARGET_PROPERTY:COMPILE_DEFINITIONS>
]]
    TARGET mainTool
)
#[========================[subject2: 21.3 不仅OUTPUT使用生成器，内容也嵌入生成器表达式]========================]

#[========================[subject3: 试试 file() 的其他功能]========================]
set(msg "Hello world")
file(WRITE hello.txt ${msg})
file(APPEND hello.txt " from CMake")
#[========================[subject3: 试试 file() 的其他功能]========================]


#[==========[]==========]
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

#[[
@brief: 尝试 14.5 节调试生成器表达式的例子，用生成文件的方式，来检测生成器表达式的值 -- subject1
        尝试 21.3 不仅 OUTPUT 可使用生成器，内容也嵌入生成器表达式；其实主要试试其他例子是否能够生成输出文件 -- subject2
        试试 file() 的其他功能 -- subject3
@author: liangj.zhang
@date: 2026/09/21

@phenomenon:
subject 1/2: 都没有文件生成； -- 目前仍然不知道为什么没能够生成；CMake 版本，和使用方式应该都没有问题，以及执行过程；
subject 3: 不涉及生成器表达式的地方，却成功生成了文件 hello.txt，在 top CMakeLists.txt 同目录下；
]]