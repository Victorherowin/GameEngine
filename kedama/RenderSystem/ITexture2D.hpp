#ifndef ITEXTURE2D
#define ITEXTURE2D

#include "ITextureBase.hpp"
#include "TextureEnum.hpp"

#include "../Config.hpp"

namespace Kedama
{
    class ITexture2D:public ITextureBase
	{
	public:
		virtual void Create(TextureFormat foramt,int w,int h)=0;
		virtual void CreateCompressFromPixels(TextureCompressFormat compress_format,TextureFormat format,int level,void* pixels,int w,int h)=0;
		virtual void CreateCompress(TextureCompressFormat compress_foramat,int level,void* data,int size,int w,int h)=0;
		virtual bool IsCompress()=0;
	};

	DEFINE_SHARED_PTR(ITexture2D)
}

#endif
