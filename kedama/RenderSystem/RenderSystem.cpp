#include "RenderSystem.hpp"
#include "../Engine.hpp"

namespace Kedama {

  void RenderSystem::SetCamera(Camera* camera)
  {
    m_main_camera=camera;
  }

  void RenderSystem::SetViewport(Viewport* vp)
  {
    m_viewport=vp;
  }

 /* void RenderSystem::Render(RenderStream* rsptr)
  {
  }*/

}
