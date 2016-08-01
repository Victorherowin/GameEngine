#ifndef GLRENDERSYSTEMFACTORY
#define GLRENDERSYSTEMFACTORY

#include "../IRenderSystemFactory.hpp"

namespace Kedama
{
  class GLRenderSystemFactory:public IRenderSystemFactory
  {
  public:
    IRenderSystem* CreateRenderSystem()override;
    void DeleteRenderSystem(IRenderSystem*)override;

    ITexture2DPtr CreateTexture2D()override;
    FrameBufferPtr CreateFrameBuffer()override;
    IVertexBufferPtr CreateVertexBuffer()override;
    IIndexBufferPtr CreateIndexBuffer()override;
  };
}

#endif
