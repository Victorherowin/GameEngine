#include "GLRenderSystemFactory.hpp"
#include "GLRenderSystem.hpp"
#include "GLShader.hpp"
#include "GLTexture2D.hpp"
#include "GLFrameBuffer.hpp"
#include "GLVertexBuffer.hpp"
#include "GLIndexBuffer.hpp"

namespace Kedama
{
  IRenderSystem* GLRenderSystemFactory::CreateRenderSystem()
  {
    IRenderSystem* irs=static_cast<IRenderSystem*>(new GLRenderSystem());
    irs->Init();
    return irs;
  }

  void GLRenderSystemFactory::DeleteRenderSystem(IRenderSystem* render_system)
  {
    render_system->Quit();
    delete dynamic_cast<GLRenderSystem*>(render_system);
  }

  FrameBufferPtr GLRenderSystemFactory::CreateFrameBuffer()
  {
    return std::make_shared<GLFrameBuffer>();
  }

  IVertexBufferPtr GLRenderSystemFactory::CreateVertexBuffer()
  {
    return std::make_shared<GLVertexBuffer>();
  }

  IIndexBufferPtr GLRenderSystemFactory::CreateIndexBuffer()
  {
    return std::make_shared<GLIndexBuffer>();
  }

  ITexture2DPtr GLRenderSystemFactory::CreateTexture2D()
  {
    return std::make_shared<GLTexture2D>();
  }
}
