#include "RenderSystem.hpp"
#include "../Engine.hpp"

namespace Kedama {

  void RenderSystem::SetCamera(const CameraPtr& camera)
  {
    m_main_camera=camera;
  }

  void RenderSystem::SetViewport(Viewport* vp)
  {
    m_viewport=vp;
  }

  void RenderSystem::Render(const RenderStreamPtr& rsptr)
  {
    if(m_use_deferred_render)
    {
      RenderStream transparent_rs;
      RenderStream no_transparent_rs;//拆分透明和不透明材质

     /* for(RenderStream::MeshInfo& mb:rsptr->GetDrawInfo())
      {
        //部分类不完善，暂时放置延迟渲染
      }*/
    }
    else
    {
      OnForwardRender(rsptr);
    }
  }

}
