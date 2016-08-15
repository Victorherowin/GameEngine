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

    static GLenum __format_table[];
    static GLenum __compress_format_table[];

  };

  DEFINE_SHARED_PTR(GLTextureBase)
}

#endif
