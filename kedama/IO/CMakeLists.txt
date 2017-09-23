cmake_minimum_required(VERSION 3.7.2)
project(Kedama_IO)

add_library(Kedama_IO ${BUILD_TYPE} ${FIIOSOURCE} FileSystem/LocalFileSystem.cpp IStream.hpp FileSystem/FileSystemContext.cpp FileSystem/FileSystemContext.hpp FileSystem/LocalFileStream.cpp FileSystem/LocalFileStream.hpp)

target_link_libraries(Kedama_IO)