#ifndef _H_GL_DEFERREDENDERER
#define _H_GL_DEFERREDRENDERER

#include "../Interface/IDeferredRenderer.hpp"
#include "GLRenderSystemClass.hpp"

namespace Kedama {
  namespace GL {
    class GLDeferredRenderer:public IDeferredRenderer
    {
    public:
      GLDeferredRenderer(GLControl* control);
      ~GLDeferredRenderer();
      void Render(const RenderCommand& cb)override;
      void Render(const MergedRenderCommand& mrc)override;
      void Finish()override;

      void SetCamera(Camera* camera)override;

    private:
      GLControl* m_control;
      Camera* m_camera;
    };
  }
}

#endif
