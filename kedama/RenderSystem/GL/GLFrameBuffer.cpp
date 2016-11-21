#include "GLFrameBuffer.hpp"
#include "GLTexture2D.hpp"

#include <GL/glew.h>

namespace Kedama
{
  static GLenum __table[4]={GL_COLOR_ATTACHMENT0,GL_DEPTH_ATTACHMENT,
                            GL_STENCIL_ATTACHMENT,GL_DEPTH_STENCIL_ATTACHMENT};


  GLFrameBuffer::GLFrameBuffer()
  {
    glGenFramebuffers(1,&m_fbo);
  }

  GLFrameBuffer::~GLFrameBuffer()
  {
    for(auto& it:m_texs)
    {
      delete it.second;
    }

    for(auto& it:m_rbos)
    {
      glDeleteRenderbuffers(1,&it.second);
    }
    glDeleteFramebuffers(1,&m_fbo);
  }

  void GLFrameBuffer::OnAttach(AttachType type)
  {
    GLenum attachment=(uint32_t)type<15?__table[0]:__table[((uint32_t)type)-15];
    if(attachment==GL_COLOR_ATTACHMENT0)
    {
      attachment+=(uint32_t)type;

      GLTexture2D* tex=new GLTexture2D;
      tex->Create(TextureFormat::SRGB,m_w,m_h);
      m_texs.push_back(std::make_pair(type,tex));

      tex->Bind();
      glBindFramebuffer(GL_FRAMEBUFFER,m_fbo);
      glFramebufferTexture2D(GL_FRAMEBUFFER,attachment,GL_TEXTURE_2D,tex->GetObj(),0);
      glBindFramebuffer(GL_FRAMEBUFFER,0);
      tex->Unbind();
    }
    else
    {
      GLuint rbo;
      glGenRenderbuffers(1,&rbo);
      m_rbos.push_back(std::make_pair(type,rbo));

      glBindRenderbuffer(GL_RENDERBUFFER,rbo);

      if(attachment==GL_DEPTH_ATTACHMENT)
      {
        glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH_COMPONENT24,m_w,m_h);
      }
      if(attachment==GL_STENCIL_ATTACHMENT)
      {
        glRenderbufferStorage(GL_RENDERBUFFER,GL_STENCIL_INDEX8,m_w,m_h);
      }
      if(attachment==GL_DEPTH_STENCIL_ATTACHMENT)
      {
        glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH24_STENCIL8,m_w,m_h);
      }

      glBindFramebuffer(GL_FRAMEBUFFER,m_fbo);
      glFramebufferRenderbuffer(GL_FRAMEBUFFER,attachment,GL_RENDERBUFFER,rbo);
      glBindFramebuffer(GL_FRAMEBUFFER,0);

      glBindRenderbuffer(GL_FRAMEBUFFER,0);

    }
  }

  void GLFrameBuffer::OnRemove(AttachType type)
  {
    GLenum attachment=__table[((int)type)-15];
    if(__table[attachment]==GL_COLOR_ATTACHMENT0)
    {
      for(auto it=m_texs.begin();it!=m_texs.end();++it)
      {
        if(it->first==type)
        {
          GLenum attachment=(((uint32_t)it->first)<15?__table[0]:__table[((uint32_t)it->first)-15])+(uint32_t)type;
          glBindFramebuffer(GL_FRAMEBUFFER,m_fbo);
          glFramebufferTexture2D(GL_FRAMEBUFFER,attachment,GL_TEXTURE_2D,0,0);
          glBindFramebuffer(GL_FRAMEBUFFER,0);
          delete it->second;
          m_texs.erase(it);
          break;
        }
      }
    }
    else
    {
      for(auto it=m_rbos.begin();it!=m_rbos.end();++it)
      {
        if(it->first==type)
        {
          GLenum attachment=(((uint32_t)it->first)<15?__table[0]:__table[((uint32_t)it->first)-15])+(uint32_t)type;
          glBindFramebuffer(GL_FRAMEBUFFER,m_fbo);
          glFramebufferRenderbuffer(GL_FRAMEBUFFER,attachment,GL_RENDERBUFFER,0);
          glBindFramebuffer(GL_FRAMEBUFFER,0);
          glDeleteRenderbuffers(1,&it->second);
          m_rbos.erase(it);
          break;
        }
      }
    }
  }

}
