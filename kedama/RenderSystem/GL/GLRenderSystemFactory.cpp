#include "GLRenderSystemFactory.hpp"
#include "GLRenderSystem.hpp"
#include "GLShader.hpp"
#include "GLTexture2D.hpp"
#include "GLFrameBuffer.hpp"
#include "GLVertexBuffer.hpp"
#include "GLIndexBuffer.hpp"

namespace Kedama
{
  RenderSystem* GLRenderSystemFactory::CreateRenderSystem()
  {
    RenderSystem* irs=static_cast<RenderSystem*>(new GLRenderSystem());
    irs->Init();
    return irs;
  }

  void GLRenderSystemFactory::DeleteRenderSystem(RenderSystem* render_system)
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
