cmake_minimum_required(VERSION 3.7.2)
project(Kedama_GLRenderSystem)

set(LIBS opengl32)

if(MSVC)

  #external libs header
  include_directories("${PROJECT_ROOT_DIR}/lib/msvc/glew/include"
                      "${PROJECT_ROOT_DIR}/lib/msvc/SDL2/include")
  #external libs
  link_directories("${PROJECT_ROOT_DIR}/lib/msvc/glew//lib/Release/Win32"
                  "${PROJECT_ROOT_DIR}/lib/msvc/SDL2/lib/x86")

  set(LIBS ${LIBS} glew32)
  set(LIBS ${LIBS} sdl2 sdl2main)
else()
  #Find GLEW
  find_package(GLEW REQUIRED)
  if(GLEW_FOUND)
    set(LIBS ${LIBS} ${GLEW_LIBRARIES})
  endif(GLEW_FOUND)

  find_package(SDL2 REQUIRED)
  if(SDL2_FOUND)
    set(LIBS ${LIBS} ${SDL2_LIBRARIES})
  endif(SDL2_FOUND)
endif()

file(GLOB GLRENDERSYSTEM_SOURCES . "*.cpp" "*.hpp" "*.inl")

add_library(Kedama_GLRenderSystem ${BUILD_TYPE} ${GLRENDERSYSTEM_SOURCES} utility/GLSmartObject.hpp GLMeshBuffer.cpp GLMeshBuffer.hpp GLSkinnedMeshBuffer.cpp GLSkinnedMeshBuffer.hpp Visitor/GLStd140UniformBlockSizeVisitor.inl Visitor/GLStd140UniformBlockVisitor.inl)

target_link_libraries(Kedama_GLRenderSystem KedamaEngine ${LIBS} opengl32)
