#ifndef GLRENDERERFACTORY
#define GLRENDERERFACTORY

#include "../Interface/IRendererFactory.hpp"
#include "../../BoneSystem/Joint.hpp"
#include "../../Define.hpp"

namespace Kedama
{
  namespace GL
  {
    class KEDAMA_API GLRenderSystemFactory:public IRendererFactory
    {
    public:
      ITexture2D* CreateTexture2D()override final;
      IMeshBuffer* CreateMeshBuffer(size_t vertex_num,size_t index_num)override final;
      ISkinner* CreateSkinner(IMeshBuffer* mesh,Joint* joint)override final;
      Material::INative* CreateMaterialNative()override final;
      Light::INative* CraeteLightNative()override final;
      IShader* CreateShader()override final;
      IControl* GetControl()override final;
      const string GetShaderLanguage()override final;
    private:
      IControl* m_control=nullptr;
    };
  }
}

#endif
