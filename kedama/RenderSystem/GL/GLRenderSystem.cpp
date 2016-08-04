//OpenGL Render System
//
//2016.7.28


#include "GLRenderSystem.hpp"
#include "GLShader.hpp"
#include "GLTexture2D.hpp"
#include "GLFrameBuffer.hpp"
#include "GLVertexBuffer.hpp"
#include "GLIndexBuffer.hpp"
#include <stdexcept>
#include <GL/glew.h>

#include "Shader/DefaultShader.cpp"
#include "Shader/GLSLPerprocessor.cpp"

namespace Kedama
{
  void GLRenderSystem::Init()
  {
    m_win.Create("Kedama",800,600);
    m_gl=SDL_GL_CreateContext(m_win.GetPtr());
    glewInit();
    if(!m_gl)
      {
        throw std::runtime_error("Create OpenGL Context Failed");
      }
    glClearColor(0.6f,0.8f,0.9f,1.0f);
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
    return "GLSL";
  }

  IShader* GLRenderSystem::CreateShader(const std::string shader_src)
  {
    GLSLPreprocessor glsl_preprocessor;
    glsl_preprocessor.Parse(shader_src);
    GLShader* r_subshader=new GLShader(glsl_preprocessor.GetVertexShader(),glsl_preprocessor.GetFragmentShader());
    return r_subshader;
  }

  void GLRenderSystem::OnForwardRender(RenderStreamPtr& rsptr)
  {
    vector<RenderStream::MaterialInfo>& mis=rsptr->GetDrawInfo();
    for(RenderStream::MaterialInfo& mi:mis)
    {

    }

  }

  void GLRenderSystem::OnDeferredRender(RenderStreamPtr& rsptr)
  {

  }
}
