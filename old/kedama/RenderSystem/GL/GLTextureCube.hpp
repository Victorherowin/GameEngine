#ifndef GLTEXTURECUBE
#define GLTEXTURECUBE

#include "../ITextureCube.hpp"
#include "GLTextureBase.hpp"

namespace Kedama
{
  class GLTextureCube:public GLTextureBase,public ITextureCube
  {
  public:

    void Create(Direction direction,TextureFormat foramt,int32_t w,int32_t h)override;
    void CreateCompressFromPixels(Direction direction,TextureCompressFormat compress_format,
                                     TextureFormat format,int32_t level,void* pixels,int32_t w,int32_t h)override;

    void CreateCompress(Direction direction,TextureCompressFormat compress_foramat,
                           int32_t level,void* data,int32_t size,int32_t w,int32_t h)override;
    bool IsCompress()override;

    void Bind();
    void Unbind();

  private:
    bool m_compress=false;
  };
}

#endif
