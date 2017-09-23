#ifndef ITEXTURE2D
#define ITEXTURE2D

#include "../../Include.hpp"
#include "../../Define.hpp"
#include "../TextureEnum.hpp"

namespace Kedama
{
  class ITexture2D
  {
  public:
    virtual void Create(TextureFormat foramt,int w,int h)=0;
    virtual void CreateCompressFromPixels(TextureCompressFormat compress_format,TextureFormat format,int level,void* pixels,int w,int h)
    {
      throw Exception::RuntimeException("No Implement");
    }
    virtual void CreateCompress(TextureCompressFormat compress_foramat,int level,void* data,int size,int w,int h)=0;
  };
}

#endif
