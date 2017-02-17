#ifndef GLRENDERERFACTORY
#define GLRENDERERFACTORY

#include "../Interface/IRendererFactory.hpp"

namespace Kedama
{
  namespace GL
  {
    class GLRenderSystemFactory:public IRendererFactory
    {
    public:
      ITexture2D* CreateTexture2D()override;
      Mesh::INative* CreateMeshNative()override;
      Material::INative* CreateMaterialNative()override;
      Shader* CreateShader(Shader::ShaderType type,const string& src)override;
      IControl* GetControl()override;
      const string GetShaderLanguage()override;
    private:
      IControl* m_control=nullptr;
    };
  }
}

#endif
