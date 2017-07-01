#ifndef _H_GL_DEFERREDENDERER
#define _H_GL_DEFERREDENDERER

#include "../Interface/IDeferredRenderer.hpp"
#include "GLRenderSystemClass.hpp"

namespace Kedama {
  namespace GL {
    class GLDeferredRenderer:public IDeferredRenderer
    {
    public:
      GLDeferredRenderer(GLControl* control);
      ~GLDeferredRenderer();
      void Render(const RenderCommand& rc)override;
      void Render(const MergedRenderCommand& mrc)override;
      void Finish()override;

    private:
      GLControl* m_control;
    };
  }
}

#endif
