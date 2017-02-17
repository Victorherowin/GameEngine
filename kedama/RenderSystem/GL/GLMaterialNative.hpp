#ifndef _H_GLMATERIALNATIVE_
#define _H_GLMATERIALNATIVE_

#include "../../Include.hpp"
#include "../Material.hpp"

namespace Kedama {
  namespace GL
  {
    using namespace std;
    class KEDAMA_API GLMaterialNative:public Material::INative
    {
    public:
      GLMaterialNative();
      ~GLMaterialNative();
      void Upload(const list<Material::Value>&)override;
      inline GLuint GetUBO()const
      {return m_ubo;}

      inline const vector<pair<string,ITexture2D*>>& GetTextures()const
      {return m_textures;}

    protected:
      GLuint m_ubo;

      vector<pair<string,ITexture2D*>> m_textures;
    };
  }
}

#endif
