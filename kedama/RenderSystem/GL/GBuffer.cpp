#include "GBuffer.hpp"

namespace Kedama {
  namespace GL {
    GBuffer::GBuffer(GLint w,GLint h)
    {
      glGenFramebuffers(1,&fbo);
      glGenTextures(3,&color_specular_tex);
      glTextureStorage2D(color_specular_tex,0,GL_RGBA16F,w,h);
      glTextureStorage2D(postion_depth_tex,0,GL_RGBA16F,w,h);
      glTextureStorage2D(normal_tex,0,GL_RGBA16F,w,h);
      glTextureParameteri(color_specular_tex,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
      glTextureParameteri(color_specular_tex,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
      glTextureParameteri(postion_depth_tex,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
      glTextureParameteri(postion_depth_tex,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
      glTextureParameteri(normal_tex,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
      glTextureParameteri(normal_tex,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    }

    GBuffer::~GBuffer()
    {
      glDeleteTextures(3,&color_specular_tex);
      glDeleteFramebuffers(1,&fbo);
    }
  }
}
