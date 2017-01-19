//OpenGL Render System
//
//2016.7.28


#include "GLRenderSystem.hpp"
#include "GLShader.hpp"
#include "GLTexture2D.hpp"

#include <stdexcept>
#include <GL/glew.h>

namespace Kedama
{
  namespace GL
  {

    GLRenderSystem::GLRenderSystem()
    {
      glGenBuffers(1,&m_model_view_ubo);
      glNamedBufferData(m_model_view_ubo,sizeof(mat4)<<1,nullptr,GL_DYNAMIC_DRAW);

    }

    void GLRenderSystem::SetCamera(Camera* camera)
    {
      if(m_main_camera!=nullptr)
        m_main_camera->GetTansform()->ClearListener();
      camera->GetTansform()->AddUpdateListener([camera,this](Transform& tf)
      {
        //TODO
      });
      RenderSystem::SetCamera(camera);
    }

    void GLRenderSystem::SetViewport(Viewport *vp)
    {
      glNamedBufferSubData(m_model_view_ubo,0,sizeof(mat4),glm::value_ptr(vp->GetProjectionMatrix()));
      RenderSystem::SetViewport(vp);
    }

    void GLRenderSystem::Init()
    {
      m_win.Create("Kedama",800,600);
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
      SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
      SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
      SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
      SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
      SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

      m_gl=SDL_GL_CreateContext(m_win.GetPtr());
      glewInit();
      if(!m_gl)
      {
        throw std::runtime_error("Create OpenGL Context Failed");
      }
      glClearColor(0.6f,0.8f,0.9f,1.0f);
      glCullFace(GL_BACK);
      glEnable(GL_DEPTH_TEST);
      glDepthFunc(GL_LESS);
    }

    void GLRenderSystem::Quit()
    {
      SDL_GL_DeleteContext(m_gl);
    }

    IWindow* GLRenderSystem::GetWindow()
    {
      return &m_win;
    }

    void GLRenderSystem::Clear()
    {
      glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    }

    void GLRenderSystem::Flush()
    {
      glFlush();
    }

    void GLRenderSystem::SwapBuffer()
    {
      SDL_GL_SwapWindow(m_win.GetPtr());
    }

    const string GLRenderSystem::GetShaderLanguage()
    {
      return "GLSL4.50";
    }
    //TODO
    /*void GLRenderSystem::OnForwardRender(const RenderStream* rsptr)
  {

  }

  void GLRenderSystem::OnDeferredRender(const RenderStream* rsptr)
  {

  }*/
  }
}
