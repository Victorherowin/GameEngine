#ifndef GLTEXTURE2D
#define GLTEXTURE2D

#include "../ITexture2D.hpp"
#include "GLTexture.hpp"

namespace Kedama {
  namespace GL
  {
    class GLTexture2D:public GLTextureBase,public ITexture2D
    {
    public:
      /*ITexture2D*/
      void Create(TextureFormat foramt,int32_t w,int32_t h)override;
      void CreateCompressFromPixels(TextureCompressFormat compress_format,TextureFormat format,int32_t level,void* pixels,int32_t w,int32_t h)override;
      void CreateCompress(TextureCompressFormat compress_foramat,int32_t level,void* data,int32_t size,int32_t w,int32_t h)override;
      //bool IsTransparent()override;
      /*GLTextureBase*/
      void Bind()override;
      void Unbind()override;

      void TexImage(GLint level,GLint internalFormat,GLsizei width,GLsizei height,GLint border,GLenum format,GLenum type,const GLvoid * data);

    private:
      bool m_compress=false;
    };
  }
}

#endif
