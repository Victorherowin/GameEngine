cmake_minimum_required(VERSION 3.7.2)
project(KedamaEngine)

option(DEBUG_BUILD "is building" ON)

file(GLOB KEDAMA_SOURCE ${PROJECT_ROOT_DIR} "*.cpp" "*.hpp" "*.inl"
				"${PROJECT_SOURCE_DIR}/RenderSystem/*.cpp" "${PROJECT_SOURCE_DIR}/RenderSystem/*.hpp"
				"${PROJECT_SOURCE_DIR}/RenderSystem/*.inl" "${PROJECT_SOURCE_DIR}/GameObject/*.cpp" 
				${PROJECT_SOURCE_DIR}/GameObject/"*.hpp" "${PROJECT_SOURCE_DIR}/GameObject/*.inl")
				
add_library(KedamaEngine ${BUILD_TYPE} ${KEDAMA_SOURCE} RenderSystem/Interface/IMeshBuffer.hpp
		RenderSystem/PropertyValue.hpp RenderSystem/PropertyValue.cpp
		RenderSystem/PropertyValueVisitor.cpp RenderSystem/PropertyValueVisitor.hpp
		RenderSystem/Interface/ITexture.hpp
		RenderSystem/Model.cpp RenderSystem/Model.hpp
		utility/Cloneable.hpp)


if(NOT MSVC)
    #find Assimp
	find_package(Assimp REQUIRED)
	if(ASSIMP_FOUND)
		message(${ASSIMP_INCLUDE_DIRS})
		include_directories(${ASSIMP_INCLUDE_DIRS})
		target_link_libraries(${ASSIMP_LIBRARIES})
	endif(ASSIMP_FOUND)

	if(DEBUG_BUILD STREQUAL ON)
		add_definitions(-DKEDAMA_DEBUG)
	endif()
else()
#external libs header
include_directories("${PROJECT_ROOT_DIR}/lib/bullet3/src"
					"${PROJECT_ROOT_DIR}/lib/assimp/code")
	if(DEBUG_BUILD STREQUAL ON)
		add_definitions(/DKEDAMA_EXPORTS /DKEDAMA_DEBUG)
	endif()
endif()

add_subdirectory(IO)
add_subdirectory(BoneSystem)
add_subdirectory(PhysicsSystem)
add_subdirectory(Exception)

if(${CMAKE_SYSTEM_NAME} STREQUAL Android)
    add_subdirectory(RenderSystem/GLES)
    target_link_libraries(KedamaEngine Kedama_GLESRenderSystem)
else()
    add_subdirectory(RenderSystem/GL)
    target_link_libraries(KedamaEngine Kedama_GLRenderSystem)
endif()
target_link_libraries(KedamaEngine Kedama_IO)


