#include "GLRenderSystemFactory.hpp"
#include "GLRenderSystem.hpp"
#include "GLShader.hpp"
#include "GLTexture2D.hpp"
#include "GLFrameBuffer.hpp"
#include "GLVertexBuffer.hpp"
#include "GLIndexBuffer.hpp"
#include "GLRenderStream.hpp"

#include "Shader/GLSLPerprocessor.cpp"

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

  VertexBufferPtr GLRenderSystemFactory::CreateVertexBuffer()
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

  RenderStreamPtr GLRenderSystemFactory::CreateRenderStream()
  {
    return std::make_shared<GLRenderStream>();
  }

  IShaderPtr GLRenderSystemFactory::CreateShader(const string& shader_src)
  {
    GLSLPreprocessor glsl_preprocessor;
    glsl_preprocessor.Parse(shader_src);
    GLShaderPtr r_shader=std::make_shared<GLShader>(glsl_preprocessor.GetVertexShader(),glsl_preprocessor.GetFragmentShader());
    return r_shader;
  }
}
