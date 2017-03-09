cmake_minimum_required(VERSION 3.0.2)
project(Kedama)

set(PROJECT_ROOT_DIR ${PROJECT_SOURCE_DIR})
set(BUILD_TYPE STATIC)

if(NOT MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -D_DEBUG")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -s")
endif()

add_subdirectory(test)
add_subdirectory(kedama)

#external libs header
include_directories("${PROJECT_ROOT_DIR}/lib/msvc/glm")

#external libs

#target_link_libraries(KedamaEngine)
