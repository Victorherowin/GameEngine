#ifndef GLRENDERSYSTEMFACTORY
#define GLRENDERSYSTEMFACTORY

#include "../IRenderSystemFactory.hpp"

namespace Kedama
{
  class GLRenderSystemFactory:public IRenderSystemFactory
  {
  public:
    RenderSystem* CreateRenderSystem()override;
    void DeleteRenderSystem(RenderSystem*)override;

    ITexture2DPtr CreateTexture2D()override;
    FrameBufferPtr CreateFrameBuffer()override;
    IVertexBufferPtr CreateVertexBuffer()override;
    IIndexBufferPtr CreateIndexBuffer()override;
  };
}

#endif
