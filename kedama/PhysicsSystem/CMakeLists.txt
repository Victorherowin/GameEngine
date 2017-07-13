cmake_minimum_required(VERSION 2.8)
project(Kedama_PhysicsSystem)

add_library(Kedama_PhysicsSystem ${BUILD_TYPE} PhysicsSystem.hpp PhysicsSystem.cpp PhysicsSystem.cpp PhysicsSystem.hpp)

#find bullet
find_package(Bullet)

if(BULLET_FOUND)
    include_directories(${BULLET_INCLUDE_DIRS})
    target_link_libraries(Kedama_PhysicsSystem ${BULLET_LIBRARIES})
endif(BULLET_FOUND)