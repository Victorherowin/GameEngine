#ifndef IRENDERSYSTEMFACTORY
#define IRENDERSYSTEMFACTORY

#include <string>
#include "RenderSystem.hpp"
#include "FrameBuffer.hpp"
#include "IShader.hpp"

namespace Kedama
{
    using std::string;

    class IRenderSystemFactory
    {
    public:
        virtual ~IRenderSystemFactory(){}
        virtual RenderSystem* CreateRenderSystem()=0;
        virtual void DeleteRenderSystem(RenderSystem*)=0;

        virtual ITexture2DPtr CreateTexture2D()=0;
        virtual FrameBufferPtr CreateFrameBuffer()=0;
        virtual VertexBufferPtr CreateVertexBuffer()=0;
        virtual IIndexBufferPtr CreateIndexBuffer()=0;
        virtual RenderStreamPtr CreateRenderStream()=0;
        virtual IShaderPtr CreateShader(const string& source)=0;
    };
}

#endif
