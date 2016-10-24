cmake_minimum_required(VERSION 2.8)
project(Kedama)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -s")
set(BUILE_TYPE SHARED)

include_directories(${PROJECT_SOURCE_DIR}/lib/glm)

add_subdirectory(test)
add_subdirectory(kedama)

target_link_libraries(KedamaEngine)
