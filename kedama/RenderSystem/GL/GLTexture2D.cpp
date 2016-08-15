#include "GLTexture2D.hpp"

namespace Kedama
{

  void GLTexture2D::Create(TextureFormat format,int32_t w,int32_t h)
  {
    m_compress=false;
    Bind();
    glTexImage2D(GL_TEXTURE_2D,0,__format_table[(int)format],w,h,0,__format_table[(int)format],GL_UNSIGNED_BYTE,nullptr);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

    Unbind();
  }

  void GLTexture2D::CreateCompressFromPixels(TextureCompressFormat compress_format,TextureFormat format
                                             ,int32_t level,void* pixels,int32_t w,int32_t h)
  {
    m_compress=true;

    Bind();
    glTexImage2D(GL_TEXTURE_2D,level,__compress_format_table[(int)compress_format],w,h,0,__format_table[(int)format],GL_UNSIGNED_BYTE,pixels);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

    Unbind();
  }

  void GLTexture2D::CreateCompress(TextureCompressFormat compress_foramat,int32_t level,void* data,int32_t size,int32_t w,int32_t h)
  {
    m_compress=true;

  }

  bool GLTexture2D::IsCompress()
  {
    return m_compress;
  }

  void GLTexture2D::Bind()
  {
    glBindTexture(GL_TEXTURE_2D,m_tex);
  }

  void GLTexture2D::Unbind()
  {
    glBindTexture(GL_TEXTURE_2D,0);
  }

  void GLTexture2D::TexImage(GLint level,GLint internalFormat,GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *data)
  {
    Bind();
    glTexImage2D(GL_TEXTURE_2D,level,internalFormat,width,height,border,format,type,data);
    Unbind();
  }
}
