cmake_minimum_required(VERSION 3.7.2)
project(Exception)



if(MSVC)
    set(BASE_EXCEPTION_SRC MSVC/Exception.cpp MSVC/Exception.hpp)
else()
    set(BASE_EXCEPTION_SRC Linux/Exception.cpp Linux/Exception.hpp)
endif()

add_library(Exception ${BUILD_TYPE} ${BASE_EXCEPTION_SRC} ExceptionCommon.hpp)