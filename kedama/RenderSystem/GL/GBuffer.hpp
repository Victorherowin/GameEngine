#ifndef _H_GBUFFER
#define _H_GBUFFER

#include "GL/glew.h"

namespace Kedama {
  namespace GL {
    class GBuffer
    {
    public:
      GLuint fbo;
      GLuint color_specular_tex;//color(3)+specular(1)
      GLuint postion_depth_tex;//postion(3)+linear depth(1)
      GLuint normal_tex;//normal(3)

      GBuffer(GLint w,GLint h);
      ~GBuffer();
    };
  }
}

#endif
