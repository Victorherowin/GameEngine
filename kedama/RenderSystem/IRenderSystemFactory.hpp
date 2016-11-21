#ifndef IRENDERSYSTEMFACTORY
#define IRENDERSYSTEMFACTORY

#include <string>
#include "RenderSystem.hpp"
#include "FrameBuffer.hpp"
#include "Shader.hpp"

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
    virtual ShaderPtr CreateShader(Shader::ShaderType type,const string& src)=0;
  };
}

#endif
