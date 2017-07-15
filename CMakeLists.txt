cmake_minimum_required(VERSION 3.7.2)
project(Kedama)

set(PROJECT_ROOT_DIR ${PROJECT_SOURCE_DIR})
set(BUILD_TYPE STATIC)
#set (CMAKE_CXX_STANDARD 17)


if(NOT MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -DDEBUG")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -s")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest /MP")
endif()

add_subdirectory(test)
add_subdirectory(kedama)

#external libs header
include_directories("${PROJECT_ROOT_DIR}/lib/msvc/glm")

#external libs

#target_link_libraries(KedamaEngine)
