#include "GLRenderSystemFactory.hpp"
#include "GLRenderSystem.hpp"
#include "GLShader.hpp"
#include "GLTexture2D.hpp"
#include "GLMeshNative.hpp"

namespace Kedama
{
  namespace GL
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

    Mesh::Native* GLRenderSystemFactory::CreateMeshNative()
    {
      return new GLMeshNative();
    }

    ITexture2D* GLRenderSystemFactory::CreateTexture2D()
    {
      return new GLTexture2D();
    }

    Shader* GLRenderSystemFactory::CreateShader(Shader::ShaderType type,const string& src)
    {
      GLShader* r_shader=new GLShader(type);
      r_shader->SetSource(src);
      return r_shader;
    }
  }
}
