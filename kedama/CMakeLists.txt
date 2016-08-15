cmake_minimum_required(VERSION 2.8)
project(KedamaEngine)

target_link_libraries(tinyxml2)

aux_source_directory(. KEDAMA_SOURCE)
aux_source_directory(RenderSystem KEDAMA_SOURCE)
aux_source_directory(GameObject KEDAMA_SOURCE)

add_library(KedamaEngine ${BUILD_TYPE} ${KEDAMA_SOURCE})

add_subdirectory(FileSystem)


if(${CMAKE_SYSTEM_NAME} STREQUAL Android)
    add_subdirectory(RenderSystem/GLES)
    target_link_libraries(Kedama_GLESRenderSystem)
else()
    add_subdirectory(RenderSystem/GL)
    target_link_libraries(Kedama_GLRenderSystem)
endif()
