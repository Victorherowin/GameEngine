#ifndef GLTEXTUREBASE
#define GLTEXTUREBASE

#include "../TextureEnum.hpp"
#include "../../Config.hpp"
#include <GL/glew.h>

namespace Kedama
{

  class GLTextureBase
  {
  public:
    GLTextureBase();
    virtual ~GLTextureBase();
    void GenerateMipmap();

    virtual void Bind()=0;
    virtual void Unbind()=0;

    inline GLuint GetObj(){return m_tex;}

  protected:
    GLuint m_tex;
  };

  DEFINE_SHARED_PTR(GLTextureBase)
}

#endif
