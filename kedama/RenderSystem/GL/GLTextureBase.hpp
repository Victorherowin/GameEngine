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
    GLuint GetGLObject();

    virtual void Bind()=0;
    virtual void Unbind()=0;

  protected:
    GLuint m_tex;
  };

  DEFINE_SHARED_PTR(GLTextureBase)
}

#endif
