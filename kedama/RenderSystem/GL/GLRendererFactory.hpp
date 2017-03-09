#ifndef GLRENDERERFACTORY
#define GLRENDERERFACTORY

#include "../Interface/IRendererFactory.hpp"
#include "../../Define.hpp"

namespace Kedama
{
  namespace GL
  {
    class KEDAMA_API GLRenderSystemFactory:public IRendererFactory
    {
    public:
      ITexture2D* CreateTexture2D()override;
      Mesh::INative* CreateMeshNative()override;
      Material::INative* CreateMaterialNative()override;
      IShader* CreateShader()override;
      IControl* GetControl()override;
      const string GetShaderLanguage()override;
    private:
      IControl* m_control=nullptr;
    };
  }
}

#endif
