cmake_minimum_required(VERSION 3.7.2)
project(Kedama_IO)

add_library(Kedama_IO ${BUILD_TYPE} ${FIIOSOURCE} FileSystem/LocalFileSystem.cpp IStream.hpp FileSystem/LocalFileStream.cpp FileSystem/LocalFileStream.hpp Path.cpp Path.hpp)

target_link_libraries(Kedama_IO)