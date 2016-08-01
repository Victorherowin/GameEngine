#ifndef IRENDERSYSTEMFACTORY
#define IRENDERSYSTEMFACTORY

#include <string>
#include "IRenderSystem.hpp"
#include "FrameBuffer.hpp"

namespace Kedama
{
	using std::string;
	
	class IRenderSystemFactory
	{
	public:
		virtual IRenderSystem* CreateRenderSystem()=0;
		virtual void DeleteRenderSystem(IRenderSystem*)=0;

		virtual ITexture2DPtr CreateTexture2D()=0;
		virtual FrameBufferPtr CreateFrameBuffer()=0;
		virtual IVertexBufferPtr CreateVertexBuffer()=0;
		virtual IIndexBufferPtr CreateIndexBuffer()=0;

	};
}

#endif
