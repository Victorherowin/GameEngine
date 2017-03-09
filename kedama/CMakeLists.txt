cmake_minimum_required(VERSION 3.0.2)
project(KedamaEngine)

option(BUILD ON)

file(GLOB KEDAMA_SOURCE ${PROJECT_ROOT_DIR} "*.cpp" "*.hpp" "*.inl"
				"${PROJECT_SOURCE_DIR}/RenderSystem/*.cpp" "${PROJECT_SOURCE_DIR}/RenderSystem/*.hpp"
				"${PROJECT_SOURCE_DIR}/RenderSystem/*.inl" "${PROJECT_SOURCE_DIR}/GameObject/*.cpp" 
				${PROJECT_SOURCE_DIR}/GameObject/"*.hpp" "${PROJECT_SOURCE_DIR}/GameObject/*.inl")
				
message(${KEDAMA_SOURCE})

add_library(KedamaEngine ${BUILD_TYPE} ${KEDAMA_SOURCE})

include_directories("${PROJECT_ROOT_DIR}/lib/msvc/glm")
if(NOT MSVC)
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DKEDAMA_EXPORTS")
else()
	if(BUILD STREQUAL ON)
		add_definitions(/DKEDAMA_EXPORTS /source-charset:utf-8)
	endif()
endif()

add_subdirectory(FileSystem)


if(${CMAKE_SYSTEM_NAME} STREQUAL Android)
    add_subdirectory(RenderSystem/GLES)
    target_link_libraries(KedamaEngine Kedama_GLESRenderSystem)
else()
    add_subdirectory(RenderSystem/GL)
    target_link_libraries(KedamaEngine Kedama_GLRenderSystem)
endif()
target_link_libraries(KedamaEngine Kedama_FileSystem)


