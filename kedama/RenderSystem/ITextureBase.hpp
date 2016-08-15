#ifndef ITEXTUREBASE
#define ITEXTUREBASE

#include "TextureEnum.hpp"
#include "../Config.hpp"

namespace Kedama
{
    class ITextureBase
    {
    public:
        virtual bool IsCompress()=0;
        //virtual bool IsTransparent()=0;
    };

    DEFINE_SHARED_PTR(ITextureBase)
}


#endif
