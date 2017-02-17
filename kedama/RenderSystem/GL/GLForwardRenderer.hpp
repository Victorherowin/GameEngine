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

      void RenderShadow(const RenderCommand& rc)override;
      void RenderShadow(const MergedRenderCommand& mrc)override;

    private:

    private:
      GLControl* m_control;

      GLuint m_plo;
    };
  }
}

#endif
