cmake_minimum_required(VERSION 3.25)
project(TestApp LANGUAGES CXX)

enable_testing()

message("PROJECT_SOURCE_DIR = ${PROJECT_SOURCE_DIR}")
message("CMAKE_SOURCE_DIR = ${CMAKE_SOURCE_DIR}")
message("CMAKE_INSTALL_PREFIX = ${CMAKE_INSTALL_PREFIX}")

#[=====================[subject1: get/set property of CACHE property, especially STRINGS]=====================]
message("=== ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt")
set(TRAFFIC_LIGHT Gray CACHE STRING "Status of Something")
get_property(resultVar CACHE TRAFFIC_LIGHT PROPERTY HELPSTRING)
message("string of cache variable :
	${resultVar}
")
unset(resultVar)
get_property(resultVar CACHE TRAFFIC_LIGHT PROPERTY TYPE)
message("type of cache variable :
	${resultVar}
")
unset(resultVar)
get_property(resultVar CACHE TRAFFIC_LIGHT PROPERTY STRINGS)
message("strings of cache variable :
	${resultVar}
")
unset(resultVar)

set_property(CACHE TRAFFIC_LIGHT PROPERTY STRINGS
	Red Orange Green
)
get_property(resultVar CACHE TRAFFIC_LIGHT PROPERTY STRINGS)
message("strings of cache variable :
	${resultVar}
")
unset(resultVar)
#[=====================[subject1: get/set property of CACHE property, especially STRINGS]=====================]


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
@brief: 尝试 set/get_property() cache variable; 尤其 STRINGS
@author: liangj.zhang
@date: 2026/09/20

@summary:
1. cache variable 的值可以不是 STRINGS 集合当中的值；
2. 可以获取 HELPSTRING/TYPE/... 等 cache variable 的属性值；
]]