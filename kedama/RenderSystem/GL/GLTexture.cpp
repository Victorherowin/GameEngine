#include "GLTexture.hpp"

namespace Kedama
{
  namespace GL
  {
    GLenum GLTextureBase::__format_table[]={GL_RGB,GL_RGBA,GL_SRGB,GL_SRGB8_ALPHA8,GL_RGB16F,GL_RGBA16F,GL_DEPTH,GL_DEPTH24_STENCIL8};
    GLenum GLTextureBase::__compress_format_table[]={GL_COMPRESSED_RGB,GL_COMPRESSED_RGBA,GL_COMPRESSED_SRGB,GL_COMPRESSED_SRGB_ALPHA,
                                                     GL_COMPRESSED_RGB_S3TC_DXT1_EXT,GL_COMPRESSED_SRGB_S3TC_DXT1_EXT,GL_COMPRESSED_RGBA_S3TC_DXT1_EXT,GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT,
                                                     GL_COMPRESSED_RGBA_S3TC_DXT3_EXT,GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT,
                                                     GL_COMPRESSED_RGBA_S3TC_DXT5_EXT,GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT,
                                                     GL_COMPRESSED_RGB8_ETC2,GL_COMPRESSED_RGBA8_ETC2_EAC};

    GLTextureBase::GLTextureBase()
    {
      glGenTextures(1,&m_tex);
    }

    GLTextureBase::~GLTextureBase()
    {
      glDeleteTextures(1,&m_tex);
    }

    void GLTextureBase::GenerateMipmap()
    {
      glGenerateMipmap(m_tex);
    }
  }
}
