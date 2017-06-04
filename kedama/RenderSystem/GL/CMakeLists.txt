cmake_minimum_required(VERSION 2.8)
project(Kedama_GLRenderSystem)

if(MSVC)

  #external libs header
  include_directories("${PROJECT_ROOT_DIR}/lib/msvc/glew/include"
                      "${PROJECT_ROOT_DIR}/lib/msvc/SDL2/include")
  #external libs
  link_directories("${PROJECT_ROOT_DIR}/lib/msvc/glew//lib/Release/Win32"
                  "${PROJECT_ROOT_DIR}/lib/msvc/SDL2/lib/x86")
endif()

file(GLOB GLRENDERSYSTEM_SOURCES . "*.cpp" "*.hpp" "*.inl")

add_library(Kedama_GLRenderSystem ${BUILD_TYPE} ${GLRENDERSYSTEM_SOURCES} utility/GLSmartObject.hpp GLMeshBuffer.cpp GLMeshBuffer.hpp GLSkinnedMeshBuffer.cpp GLSkinnedMeshBuffer.hpp)

target_link_libraries(Kedama_GLRenderSystem KedamaEngine SDL2 SDL2main opengl32 glew32)
