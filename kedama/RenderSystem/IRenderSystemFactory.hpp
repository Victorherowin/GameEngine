#ifndef IRENDERSYSTEMFACTORY
#define IRENDERSYSTEMFACTORY

#include <string>
#include "RenderSystem.hpp"
#include "FrameBuffer.hpp"

namespace Kedama
{
	using std::string;
	
	class IRenderSystemFactory
	{
	public:
                virtual RenderSystem* CreateRenderSystem()=0;
                virtual void DeleteRenderSystem(RenderSystem*)=0;

		virtual ITexture2DPtr CreateTexture2D()=0;
		virtual FrameBufferPtr CreateFrameBuffer()=0;
		virtual IVertexBufferPtr CreateVertexBuffer()=0;
		virtual IIndexBufferPtr CreateIndexBuffer()=0;

	};
}

#endif
