#ifndef _H_IRENDERERFACTORY
#define _H_IRENDERERFACTORY

#include <string>
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

    virtual Mesh::INative* CreateMeshNative()=0;
    virtual Material::INative* CreateMaterialNative()=0;
	virtual Light::INative* CraeteLightNative() = 0;

    virtual IControl* GetControl()=0;
  };
}

#endif
