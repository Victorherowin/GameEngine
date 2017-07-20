cmake_minimum_required(VERSION 3.1.0)
project(LIBS)

#Assimp
set(ASSIMP_BUILD_TESTS OFF)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF)

#Bullet
set(BUILD_UNIT_TESTS OFF)
set(BUILD_CPU_DEMOS OFF)
set(BUILD_BULLET2_DEMOS OFF)
set(BUILD_PYBULLET OFF)

if(MSVC)
	add_definitions("/DGTEST_ENV_HAS_STD_TUPLE_")
	#third party libs
	add_subdirectory(bullet3)
	add_subdirectory(assimp)
else()
	add_definitions("-DGTEST_ENV_HAS_STD_TUPLE_")
endif(MSVC)