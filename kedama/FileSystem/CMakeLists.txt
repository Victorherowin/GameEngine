cmake_minimum_required(VERSION 3.7.2)
project(Kedama_FileSystem)

aux_source_directory(. FILESYSTEM_SOURCE)

add_library(Kedama_FileSystem ${BUILD_TYPE} ${FILESYSTEM_SOURCE} FileSystem.cpp Stream.cpp)

target_link_libraries(Kedama_FileSystem)