#ifndef ITEXTURE2D
#define ITEXTURE2D

#include "ITextureBase.hpp"
#include "TextureEnum.hpp"

#include "../Config.hpp"

namespace Kedama
{
    DEFINE_SHARED_PTR(ITexture2D)

    class ITexture2D:public ITextureBase
    {
    public:
        virtual void Create(TextureFormat foramt,int w,int h)=0;
        virtual void CreateCompressFromPixels(TextureCompressFormat compress_format,TextureFormat format,int level,void* pixels,int w,int h)
        {
            throw std::runtime_error("No Implement");
        }
        virtual void CreateCompress(TextureCompressFormat compress_foramat,int level,void* data,int size,int w,int h)=0;
        virtual bool IsCompress()=0;
        //virtual bool IsTransparent()=0;
    };
}

#endif
