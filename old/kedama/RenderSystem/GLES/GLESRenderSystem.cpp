#include "GLES/GLESRenderSystem.hpp"

#include <stdexcept>
#include <GLES3/gl3.h>

namespace Kedama
{
	void GLESRenderSystem::Init()
	{
		m_win.Create("",800,600);
		m_gl=SDL_GL_CreateContext(m_win.GetPtr());
		if(!m_gl)
		{
			throw std::runtime_error("Create OpenGL Context Failed");
		}
		glClearColor(0.6f,0.8f,0.9f,1.0f);
	}
	
	void GLESRenderSystem::Quit()
	{
		SDL_GL_DeleteContext(m_gl);
	}
	
	void GLESRenderSystem::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	}
	
	void GLESRenderSystem::Flush()
	{
		glFlush();
	}
	
	void GLESRenderSystem::SwapBuffer()
	{
		SDL_GL_SwapWindow(m_win.GetPtr());
	}
	
	void GLESRenderSystem::DrawRect(glm::vec2 pos1,glm::vec2 pos2,glm::vec4 color)
	{
		
	}
	
	void GLESRenderSystem::DrawGameObject(GameObject*)
	{
		
	}
}