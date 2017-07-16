cmake_minimum_required(VERSION 3.7.2)
project(Exception)

if(WIN32)
    set(BASE_EXCEPTION_SRC Windows/Exception.cpp Windows/Exception.hpp)
else()
    set(BASE_EXCEPTION_SRC Linux/Exception.cpp Linux/Exception.hpp)
endif(WIN32)

add_library(Exception ${BUILD_TYPE} ${BASE_EXCEPTION_SRC} ExceptionCommon.hpp RuntimeException.cpp RuntimeException.hpp)

if(WIN32)
	if(NOT MSVC)
		set(LIBS backtrace)
	endif(NOT MSVC)
	set(LIBS ${LIBS} DbgHelp)
else()
	set(LIBS backtrace)
endif(WIN32)

target_link_libraries(Exception ${LIBS})