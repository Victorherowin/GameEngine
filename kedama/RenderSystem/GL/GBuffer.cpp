#include "GBuffer.hpp"

namespace Kedama {
  namespace GL {
    GBuffer::GBuffer()
    {
      glGenFramebuffers(1,&fbo);
    }

    void GBuffer::AddTexture(GLint w, GLint h, GLenum format,GLenum attach_target)
    {
      GLuint tex;
      glGenTextures(1,&tex);
      glTextureStorage2D(tex,0,format,w,h);
      glTextureParameteri(tex,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
      glTextureParameteri(tex,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
      glNamedFramebufferTexture(fbo,attach_target,tex,0);
      texs.push_back(tex);
    }

    GBuffer::~GBuffer()
    {
      for(auto tex:texs)
        glDeleteTextures(1,&tex);
      glDeleteFramebuffers(1,&fbo);
    }
  }
}
