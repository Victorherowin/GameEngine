cmake_minimum_required(VERSION 2.8)
project(Kedama_BoneSystem)

aux_source_directory(. BONESYSTEM_SOURCE)

add_library(Kedama_BoneSystem ${BUILD_TYPE} ${BONESYSTEM_SOURCE})

target_link_libraries(Kedama_BoneSystem)
