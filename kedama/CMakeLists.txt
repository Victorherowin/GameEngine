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

#find Assimp
find_package(Assimp REQUIRED)
include_directories(KedamaEngine ${ASSIMP_INCLUDE_DIRS})
target_link_libraries(KedamaEngine ${ASSIMP_LIBRARIES})

if(NOT MSVC)
	if(DEBUG_BUILD STREQUAL ON)
		add_definitions(-DKEDAMA_DEBUG)
	endif()
else()
	#external libs header
	if(DEBUG_BUILD STREQUAL ON)
		add_definitions(/DKEDAMA_EXPORTS /DKEDAMA_DEBUG)
	endif()
endif()

add_subdirectory(IO)
add_subdirectory(BoneSystem)
add_subdirectory(PhysicsSystem)

if(${CMAKE_SYSTEM_NAME} STREQUAL Android)
    add_subdirectory(RenderSystem/GLES)
    target_link_libraries(KedamaEngine Kedama_GLESRenderSystem)
else()
    add_subdirectory(RenderSystem/GL)
    target_link_libraries(KedamaEngine Kedama_GLRenderSystem)
endif()
target_link_libraries(KedamaEngine Kedama_IO)


