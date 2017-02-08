#ifndef _H_GL_FORWARDRENDERER
#define _H_GL_FORWARDRENDERER

#include "../Interface/IForwardRenderer.hpp"
#include "GLRenderSystemClass.hpp"

namespace Kedama {
  namespace GL {
    class GLForwardRenderer:public IForwardRenderer
    {
    public:
      GLForwardRenderer(GLControl* control);
      ~GLForwardRenderer();

      void Render(const RenderCommand& rc)override;
      void Render(const MergedRenderCommand& mrc)override;
      void SetCamera(Camera* camera)override;
    private:

    private:
      GLControl* m_control;
      Camera* m_camera;


    };
  }
}

#endif
