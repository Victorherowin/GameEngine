#ifndef ITEXTURECUBE
#define ITEXTURECUBE

#include "ITextureBase.hpp"

namespace Kedama
{
    class ITextureCube:public ITextureBase
    {
    public:
        enum class Direction
        {
            POSITIVE_X,NEGATIVE_X,POSITIVE_Y,NEGATIVE_Y,POSITIVE_Z,NEGATIVE_Z
        };

    public:
        virtual void Create(Direction direction,TextureFormat format,int32_t w,int32_t h)=0;
        virtual void CreateCompressFromPixels(Direction direction,TextureCompressFormat compress_format,
                                         TextureFormat format,int32_t level,void* pixels,int32_t w,int32_t h)
        {
            throw std::runtime_error("No Implement");
        }
        virtual void CreateCompress(Direction direction,TextureCompressFormat compress_foramat,
                               int32_t level,void* data,int32_t size,int32_t w,int32_t h)=0;
    };
}

#endif
