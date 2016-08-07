#include "GLFrameBuffer.hpp"
#include "GLTexture2D.hpp"

#include <GL/glew.h>

namespace Kedama
{
  GLFrameBuffer::GLFrameBuffer()
  {
    glGenFramebuffers(1,&m_fbo);
  }

  GLFrameBuffer::~GLFrameBuffer()
  {
    for(GLTexture2D* tex:m_texs)
    {
      delete tex;
    }
    if(!m_rbos.empty())
    {
      glDeleteRenderbuffers(m_rbos.size(),&m_rbos[0]);
    }
    glDeleteFramebuffers(1,&m_fbo);
  }

  void GLFrameBuffer::OnAttach(AttachType type)
  {
    static GLenum __table[4]={GL_COLOR_ATTACHMENT0,GL_DEPTH_ATTACHMENT,GL_STENCIL_ATTACHMENT,GL_DEPTH_STENCIL_ATTACHMENT};
    GLenum attachment=__table[((int)type)-15];
    if(attachment==GL_COLOR_ATTACHMENT0)
    {
      attachment+=(uint32_t)type;

      GLTexture2D* tex=new GLTexture2D;
      tex->Create(TextureFormat::SRGB,m_w,m_h);
      m_texs.push_back(tex);

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
      m_rbos.push_back(rbo);

      glBindRenderbuffer(GL_FRAMEBUFFER,rbo);

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
      glBindRenderbuffer(GL_FRAMEBUFFER,0);

    }
  }

}
