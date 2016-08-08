cmake_minimum_required(VERSION 2.8)
project(Kedama_GLRenderSystem)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/lib/glm)
include_directories(${PROJECT_SOURCE_DIR}/src/GL/Shader)


aux_source_directory(. GLRENDERSYSTEM_SOURCE)

add_library(Kedama_GLRenderSystem ${GLRENDERSYSTEM_SOURCE})

target_link_libraries(Kedama_GLRenderSystem KedamaEngine SDL2 SDL2main SDL2_image opengl32 glew32)
