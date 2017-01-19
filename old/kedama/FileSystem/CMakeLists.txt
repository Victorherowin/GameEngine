cmake_minimum_required(VERSION 2.8)
project(Kedama_FileSystem)

include_directories(${PROJECT_SOURCE_DIR}/include/FileSystem)


aux_source_directory(. FILESYSTEM_SOURCE)

add_library(Kedama_FileSystem ${BUILD_TYPE} ${FILESYSTEM_SOURCE})

target_link_libraries(Kedama_FileSystem)
