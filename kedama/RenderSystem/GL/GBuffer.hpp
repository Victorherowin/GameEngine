#ifndef _H_GBUFFER
#define _H_GBUFFER

#include "GL/glew.h"
#include "../../Include.hpp"

namespace Kedama {
  namespace GL {
    class GBuffer
    {
    public:
      GLuint fbo;
      std::vector<GLuint> texs;

      GBuffer();
      void AddTexture(GLint w,GLint h,GLenum format,GLenum attach_target);
      ~GBuffer();
    };
  }
}

#endif
