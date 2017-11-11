cmake_minimum_required(VERSION 3.7.2)
project(Kedama_GLRenderSystem)

#Add SRC
file(GLOB GLRENDERSYSTEM_SOURCES . "*.cpp" "*.hpp" "*.inl")
add_library(Kedama_GLRenderSystem ${BUILD_TYPE} ${GLRENDERSYSTEM_SOURCES} utility/GLSmartObject.hpp GLMeshBuffer.cpp GLMeshBuffer.hpp GLSkinnedMeshBuffer.cpp GLSkinnedMeshBuffer.hpp Visitor/GLStd140UniformBlockSizeVisitor.inl Visitor/GLStd140UniformBlockVisitor.inl)

target_link_libraries(Kedama_GLRenderSystem KedamaEngine)

#Find OpenGL
find_package(OPENGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
target_link_libraries(Kedama_GLRenderSystem ${OPENGL_LIBRARIES})

 #Find GLEW
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIR})
target_link_libraries(Kedama_GLRenderSystem ${GLEW_LIBRARIES})

#Find SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
target_link_libraries(Kedama_GLRenderSystem SDL2 SDL2main)