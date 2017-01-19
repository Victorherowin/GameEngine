#ifndef GLRENDERSYSTEMFACTORY
#define GLRENDERSYSTEMFACTORY

#include "../IRenderSystemFactory.hpp"

namespace Kedama
{
  namespace GL
  {
    class GLRenderSystemFactory:public IRenderSystemFactory
    {
    public:
      RenderSystem* CreateRenderSystem()override;
      void DeleteRenderSystem(RenderSystem*)override;

      ITexture2D* CreateTexture2D()override;
      Mesh::Native* CreateMeshNative()override;
      Shader* CreateShader(Shader::ShaderType type,const string& src)override;
    };
  }
}

#endif
