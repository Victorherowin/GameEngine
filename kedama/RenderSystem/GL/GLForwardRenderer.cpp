#include "GLForwardRenderer.hpp"

namespace Kedama {
  namespace GL {
    GLForwardRenderer::GLForwardRenderer(GLControl* control):m_control(control)
    {

    }

    void GLForwardRenderer::SetCamera(Camera *camera)
    {
      m_camera=camera;
    }

    void GLForwardRenderer::Render(const RenderCommand& rc)
    {

    }
  }
}
