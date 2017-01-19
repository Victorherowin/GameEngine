cmake_minimum_required(VERSION 2.8)
project(Kedama_GLESRenderSystem)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/lib/glm)


aux_source_directory(. GLESRenderSystem_SOURCE)

add_library(Kedama_GLESRenderSystem ${GLESRenderSystem_SOURCE})

target_link_libraries(Kedama_GLESRenderSystem SDL2 SDL2main GLESv1_CM GLESv3)

if(ANDROID)
	target_link_libraries(Kedama_GLESRenderSystem android log)
endif()