#ifndef _H_GLMATERIALNATIVE_
#define _H_GLMATERIALNATIVE_

#include "../../Include.hpp"
#include "../Material.hpp"
#include "GL/glew.h"

namespace Kedama {
  namespace GL
  {
    using namespace std;
    class KEDAMA_API GLMaterialNative:public Material::INative
    {
    public:
      GLMaterialNative();
      ~GLMaterialNative();
      void Init(const list<AbstractPropertyValue*>&)override;
      inline GLuint GetUBO()const
      {return m_ubo;}

      inline const vector<pair<string,ITexture2D*>>& GetTextures()const
      {return m_textures;}

    protected:
      GLuint m_ubo=0;
      int m_last_size=0;

      vector<pair<string,ITexture2D*>> m_textures;
    };
  }
}

#endif
