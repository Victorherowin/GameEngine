#ifndef _H_GL_POSTPROCESSOR
#define _H_GL_POSTPROCESSOR

#include "../Interface/IPostProcessor.hpp"
#include "GLRenderSystemClass.hpp"

namespace Kedama {
  namespace GL {
    class GLPostProcessor:public IPostProcessor
    {
    public:
      GLPostProcessor(GLControl* control);
      ~GLPostProcessor();

      void PostProcess(const PostProcessCommand& ppc)override;

    private:
      GLControl* m_control;
    };
  }
}

#endif
