#ifndef ITEXTURE2D
#define ITEXTURE2D

#include "ITexture.hpp"

#include "../Define.hpp"

namespace Kedama
{

//TODO:TextureCube的面 转Texture2D
  class ITexture2D:public ITexture
  {
  public:
    virtual void Create(TextureFormat foramt,int w,int h)=0;
    virtual void CreateCompressFromPixels(TextureCompressFormat compress_format,TextureFormat format,int level,
                                        void* pixels,int w,int h)
    {
      throw std::runtime_error("No Implement");
    }
    virtual void CreateCompress(TextureCompressFormat compress_foramat,int level,void* data,int size,int w,int h)=0;
  };
}

#endif
