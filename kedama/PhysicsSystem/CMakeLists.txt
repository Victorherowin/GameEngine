cmake_minimum_required(VERSION 3.7.2)
project(Kedama_PhysicsSystem)

add_library(Kedama_PhysicsSystem ${BUILD_TYPE} PhysicsSystem.hpp PhysicsSystem.cpp PhysicsSystem.cpp PhysicsSystem.hpp)


if(MSVC)

elseif()

#find bullet
	find_package(Bullet REQUIRED)
	if(BULLET_FOUND)
		include_directories(${BULLET_INCLUDE_DIRS})
		target_link_libraries(Kedama_PhysicsSystem ${BULLET_DYNAMICS_LIBRARY} ${BULLET_COLLISION_LIBRARY} ${BULLET_MATH_LIBRARY} ${BULLET_SOFTBODY_LIBRARY})
	endif(BULLET_FOUND)
endif(MSVC)