#ifndef _H_IRENDERERFACTORY
#define _H_IRENDERERFACTORY

#include <string>
#include "../../BoneSystem/ISkinner.hpp"
#include "../../BoneSystem/Joint.hpp"
#include "../RenderSystem.hpp"
#include "../Interface/IShader.hpp"
#include "ITexture2D.hpp"
#include "../MeshRenderer.hpp"
#include "IControl.hpp"


namespace Kedama
{
  using namespace std;
  using namespace glm;

  class KEDAMA_API IRendererFactory
  {
  public:
    virtual ~IRendererFactory(){}

    virtual const string GetShaderLanguage()=0;

    virtual ITexture2D* CreateTexture2D()=0;
    virtual IShader* CreateShader()=0;

    virtual IMeshBuffer* CreateMeshBuffer(size_t vertex_num,size_t index_num)=0;
    virtual ISkinner* CreateSkinner(IMeshBuffer* mesh,Joint* joint)=0;

    virtual Material::INative* CreateMaterialNative()=0;
	virtual Light::INative* CraeteLightNative() = 0;

    virtual IControl* GetControl()=0;
  };
}

#endif
