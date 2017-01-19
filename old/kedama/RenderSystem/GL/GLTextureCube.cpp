#include "GLTextureCube.hpp"

namespace Kedama {
  static GLenum __direction_table[]={GL_TEXTURE_CUBE_MAP_POSITIVE_X,GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
                                     GL_TEXTURE_CUBE_MAP_POSITIVE_Y,GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
                                     GL_TEXTURE_CUBE_MAP_POSITIVE_Z,GL_TEXTURE_CUBE_MAP_NEGATIVE_Z};

  void GLTextureCube::Create(Direction direction,TextureFormat format, int32_t w, int32_t h)
  {
    GLenum di=__direction_table[(int)direction];

    m_compress=false;

    Bind();
    glTexImage2D(di,0,__format_table[(int)format],w,h,0,__format_table[(int)format],GL_UNSIGNED_BYTE,nullptr);

    glTexParameteri(di,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(di,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(di,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(di,GL_TEXTURE_WRAP_T,GL_REPEAT);
    Unbind();
  }

  void GLTextureCube::CreateCompressFromPixels(Direction direction,TextureCompressFormat compress_format,
                                               TextureFormat format,int32_t level,void* pixels,int32_t w,int32_t h)
  {
    GLenum di=__direction_table[(int)direction];

    m_compress=true;

    Bind();
    glTexImage2D(di,level,__compress_format_table[(int)compress_format],w,h,0,__format_table[(int)format],GL_UNSIGNED_BYTE,pixels);

    glTexParameteri(di,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(di,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(di,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(di,GL_TEXTURE_WRAP_T,GL_REPEAT);

    Unbind();
  }

  void GLTextureCube::CreateCompress(Direction direction, TextureCompressFormat compress_foramat,
                                     int32_t level, void *data, int32_t size, int32_t w, int32_t h)
  {
    m_compress=true;


  }

  bool GLTextureCube::IsCompress()
  {
    return m_compress;
  }

  void GLTextureCube::Bind()
  {
    glBindTexture(GL_TEXTURE_CUBE_MAP,m_tex);
  }

  void GLTextureCube::Unbind()
  {
    glBindTexture(GL_TEXTURE_CUBE_MAP,0);
  }
}
