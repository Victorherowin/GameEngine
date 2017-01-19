#ifndef _H_GLMATERIALNATIVE_
#define _H_GLMATERIALNATIVE_

#include "../../Include.hpp"
#include "../Material.hpp"

namespace Kedama {
  namespace GL
  {
    using namespace std;
    class KEDAMA_API GLMaterialNative:public Material::Native
    {
    public:
      GLMaterialNative();
      ~GLMaterialNative();
      void Upload(const list<Material::Value>&)override;

    protected:
      GLuint m_ubo;
      vector<pair<string,ITexture*>> m_textures;
    };
  }
}

#endif
