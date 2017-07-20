cmake_minimum_required(VERSION 3.7.2)
project(Kedama)

set(PROJECT_ROOT_DIR ${PROJECT_SOURCE_DIR})
set(BUILD_TYPE STATIC)
#set (CMAKE_CXX_STANDARD 17)

include_directories("${PROJECT_ROOT_DIR}/lib/glm")

if(NOT MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -s")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest /MP /source-charset:utf-8")
endif()

add_subdirectory(test)
add_subdirectory(kedama)

#third party libs
add_subdirectory(lib)


#target_link_libraries(KedamaEngine)
