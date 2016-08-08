#ifndef TEXTUREENUM
#define TEXTUREENUM

namespace Kedama
{
    enum class TextureFormat
    {
        RGB,RGBA,SRGB,SRGBA,RGB16F,RGBA16F,DEPTH,DEPTH_STENCIL
    };

    enum class TextureCompressFormat
    {
        RGB,RGBA,SRGB,SRGBA,RGB_DXT1,SRGB_DXT1,RGBA_DXT1,SRGBA_DXT1,RGBA_DXT3,SRGBA_DXT3,
        RGBA_DXT5,SRGBA_DXT5,RGB_ETC2,RGBA_ETC2_EAC
    };

}
#endif /*ITEXTUREBASE*/
