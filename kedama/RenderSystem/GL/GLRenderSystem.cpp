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
    return "GLSL";
  }

  void GLRenderSystem::OnForwardRender(const RenderStreamPtr& rsptr)
  {
    GLRenderStreamPtr glrsptr=std::dynamic_pointer_cast<GLRenderStream>(rsptr);
    vector<GLRenderStream::MeshInfo>& mis=glrsptr->GetDrawInfo();

    for(GLRenderStream::MeshInfo& mi:mis)
    {
      if(mi.m_instancing_info.Empty())continue;

      GLIndexBufferPtr ibo=std::dynamic_pointer_cast<GLIndexBuffer>(mi.mesh_buffer.second);
      GLTexture2DPtr tex2d=std::dynamic_pointer_cast<GLTexture2D>(mi.material->GetTexture());

      const vector<Pass>& pass=mi.material->GetPass();
      auto& vaos=glrsptr->GetVAOs();
      GLuint vao=vaos[&mi];

      if(tex2d!=nullptr)
      {
        tex2d->Bind();
      }
      glBindVertexArray(vao);

      for(const Pass& subpass:pass)
      {
        GLFrameBufferPtr src_fb=std::dynamic_pointer_cast<GLFrameBuffer>(subpass.m_src_framebuffer);

        if(src_fb!=nullptr)
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

        int tex_n=1;

        /*
         *
         * 贴图设置（等待补完）
        */

        if(src_fb!=nullptr)
        {
          auto it=src_fb->GetGLTextureObjs().begin();
          for(int i=tex_n;i<src_fb->GetGLTextureObjs().size();++i)
          {
            glActiveTexture(GL_TEXTURE0+i);
            it->second->Bind();
            it++;
            glUniform1i(i,i);
          }
        }

        if(mi.m_instancing_info.GetSize()==1)
        {
          GLint model_mat_loc=glGetUniformLocation(shader->GetShader(),"kedama_model_matrix");
          glUniformMatrix4fv(model_mat_loc,1,GL_FALSE,glm::value_ptr(mi.m_instancing_info.GetTransformPtr(0)->GetModelMatrix()));
          glDrawElements(GL_TRIANGLES,ibo->GetSize(),GL_UNSIGNED_INT,nullptr);
        }
        else
        {
          //多实例渲染....
        }

        if(src_fb!=nullptr)
        {
          auto it=src_fb->GetGLTextureObjs().begin();
          for(int i=1;i<src_fb->GetGLTextureObjs().size();++i)
          {
            glActiveTexture(GL_TEXTURE0+i);
            it->second->Unbind();
          }
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

  void GLRenderSystem::OnDeferredRender(const RenderStreamPtr& rsptr)
  {

  }
}
