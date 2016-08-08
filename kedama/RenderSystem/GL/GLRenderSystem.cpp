//OpenGL Render System
//
//2016.7.28


#include "GLRenderSystem.hpp"
#include "GLShader.hpp"
#include "GLTexture2D.hpp"
#include "GLFrameBuffer.hpp"
#include "GLVertexBuffer.hpp"
#include "GLIndexBuffer.hpp"
#include "GLRenderStream.hpp"
#include <stdexcept>
#include <GL/glew.h>

#include "Shader/DefaultShader.cpp"

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
    glCullFace(GL_BACK);
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

  void GLRenderSystem::OnForwardRender(RenderStreamPtr& rsptr)
  {
    GLRenderStreamPtr glrsptr=std::dynamic_pointer_cast<GLRenderStream>(rsptr);
    vector<GLRenderStream::MaterialInfo>& mis=glrsptr->GetDrawInfo();
    for(GLRenderStream::MaterialInfo& mi:mis)
    {
      //GLVertexBufferPtr vbo=std::dynamic_pointer_cast<GLVertexBuffer>(mi.mesh_buffer.first);
      GLIndexBufferPtr ibo=std::dynamic_pointer_cast<GLIndexBuffer>(mi.mesh_buffer.second);
      GLTexture2DPtr tex2d=std::dynamic_pointer_cast<GLTexture2D>(mi.material->GetTexture());
      const vector<Pass> pass=mi.material->GetPass();
      auto& vaos=glrsptr->GetVAOs();
      GLuint vao=vaos[&mi];
      if(tex2d!=nullptr)
      {
        tex2d->Bind();
      }
      glBindVertexArray(vao);
      for(const Pass& subpass:pass)
      {
        if(subpass.m_dst_framebuffer!=nullptr)
        {
          GLFrameBufferPtr dst_fb=std::dynamic_pointer_cast<GLFrameBuffer>(subpass.m_dst_framebuffer);
          glBindFramebuffer(GL_DRAW_FRAMEBUFFER,dst_fb->GetObj());
        }

        GLShaderPtr shader=std::dynamic_pointer_cast<GLShader>(subpass.m_shader);
        glUseProgram(shader->GetShader());
        if(m_main_camera!=nullptr)
        {
          shader->SetViewMatrix(m_main_camera->GetViewMatrix());
          shader->SetProjectionMatrix(m_main_camera->GetProjectionMatrix());
        }


        if(subpass.m_src_framebuffer!=nullptr)
        {
          GLFrameBufferPtr src_fb=std::dynamic_pointer_cast<GLFrameBuffer>(subpass.m_src_framebuffer);

          for(int i=1;i<src_fb->GetGLTextureObjs().size();++i)
          {
            glActiveTexture(GL_TEXTURE0+i);
            src_fb->GetGLTextureObjs()[i]->Bind();
            glUniform1i(i,i);
          }

          glDrawElements(GL_TRIANGLES,ibo->GetSize(),GL_UNSIGNED_INT,nullptr);

          for(int i=1;i<src_fb->GetGLTextureObjs().size();++i)
          {
            glActiveTexture(GL_TEXTURE0+i);
            src_fb->GetGLTextureObjs()[i]->Unbind();
          }
        }
        else
        {
          glDrawElements(GL_TRIANGLES,ibo->GetSize(),GL_UNSIGNED_INT,nullptr);
        }

        glBindFramebuffer(GL_DRAW_FRAMEBUFFER,0);
        glActiveTexture(GL_TEXTURE0);
        glUseProgram(0);
      }
      glBindVertexArray(0);
      if(tex2d!=nullptr)
      {
        tex2d->Unbind();
      }
    }

  }

  void GLRenderSystem::OnDeferredRender(RenderStreamPtr& rsptr)
  {

  }
}
