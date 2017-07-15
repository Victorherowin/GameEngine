cmake_minimum_required(VERSION 3.7.2)
project(Kedama_BoneSystem)

file(GLOB BONESYSTEM_SOURCE . "*.cpp" "*.hpp" "*.inl")

add_library(Kedama_BoneSystem ${BUILD_TYPE} ${BONESYSTEM_SOURCE})

target_link_libraries(Kedama_BoneSystem)
