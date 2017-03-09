cmake_minimum_required(VERSION 2.8)
project(Kedama_test)

set(TEST_SOURCE Init.cpp)
set(LINK_LIBS KedamaEngine Kedama_FileSystem)

include_directories("${PROJECT_ROOT_DIR}/kedama"
				   "${PROJECT_ROOT_DIR}/lib/msvc/glm"
				   "${PROJECT_ROOT_DIR}/lib/msvc/glew/include"
				   "${PROJECT_ROOT_DIR}/lib/msvc/SDL2/include")
link_directories("${PROJECT_ROOT_DIR}/lib/msvc/glew//lib/Release/Win32"
				 "${PROJECT_ROOT_DIR}/lib/msvc/SDL2/lib/x86")

if(${CMAKE_SYSTEM_NAME} STREQUAL Android)
    set(LINK_LIBS ${LINK_LIBS} Kedama_GLESRenderSystem)
else()
     set(LINK_LIBS ${LINK_LIBS} Kedama_GLRenderSystem)
endif()

foreach(i ${TEST_SOURCE})
	add_executable("Kedama_test_${i}" ${i})
	target_link_libraries("Kedama_test_${i}" ${LINK_LIBS})
endforeach()
