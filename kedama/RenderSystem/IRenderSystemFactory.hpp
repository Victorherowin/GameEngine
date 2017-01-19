#ifndef _H_IRENDERSYSTEMFACTORY
#define _H_IRENDERSYSTEMFACTORY

#include <string>
#include "RenderSystem.hpp"
#include "Shader.hpp"
#include "ITexture2D.hpp"
#include "MeshRenderer.hpp"

namespace Kedama
{
  using namespace std;
  using namespace glm;

  class IRenderSystemFactory
  {
  public:
    virtual ~IRenderSystemFactory(){}
    virtual RenderSystem* CreateRenderSystem()=0;
    virtual void DeleteRenderSystem(RenderSystem*)=0;

    virtual ITexture2D* CreateTexture2D()=0;
    virtual Mesh::Native* CreateMeshNative()=0;
    virtual Shader* CreateShader(Shader::ShaderType type,const string& src)=0;
  };
}

#endif
