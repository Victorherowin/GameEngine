#include "GLTexture2D.hpp"

namespace Kedama
{
  namespace GL
  {
    void GLTexture2D::Create(TextureFormat format,int32_t w,int32_t h)
    {
      m_compress=false;
      glTextureStorage2D(m_tex,0,__format_table[(int)format],w,h);

      glTextureParameteri(m_tex,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
      glTextureParameteri(m_tex,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
      glTextureParameteri(m_tex,GL_TEXTURE_WRAP_S,GL_REPEAT);
      glTextureParameteri(m_tex,GL_TEXTURE_WRAP_T,GL_REPEAT);

    }

    void GLTexture2D::CreateCompressFromPixels(TextureCompressFormat compress_format,TextureFormat format,int32_t level,void* pixels,int32_t w,int32_t h)
    {
      m_compress=true;

      glTextureStorage2D(m_tex,level,__compress_format_table[(int)compress_format],w,h);
      glTextureSubImage2D(m_tex,level,0,0,w,h,__format_table[(int)format],GL_UNSIGNED_BYTE,pixels);

      glTextureParameteri(m_tex,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
      glTextureParameteri(m_tex,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
      glTextureParameteri(m_tex,GL_TEXTURE_WRAP_S,GL_REPEAT);
      glTextureParameteri(m_tex,GL_TEXTURE_WRAP_T,GL_REPEAT);
    }

    void GLTexture2D::CreateCompress(TextureCompressFormat compress_foramat,int32_t level,void* data,int32_t size,int32_t w,int32_t h)
    {
      m_compress=true;

    }

    void GLTexture2D::Bind()
    {
      glBindTexture(GL_TEXTURE_2D,m_tex);
    }

    void GLTexture2D::Unbind()
    {
      glBindTexture(GL_TEXTURE_2D,0);
    }

    void GLTexture2D::UpdateImage(GLint level,GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *data)
    {
      glTextureSubImage2D(m_tex,level,0,0,width,height,format,type,data);
    }
  }
}
