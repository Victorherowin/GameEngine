#include "RenderSystem.hpp"

namespace Kedama {

  void RenderSystem::SetCamera(CameraPtr camera)
  {
    m_main_camera=camera;
  }

  void RenderSystem::Render(RenderStreamPtr& rsptr)
  {
    if(m_use_deferred_render)
    {
      RenderStreamPtr transparent_rs=RenderStream::CreateRenderStream();
      RenderStreamPtr no_transparent_rs=RenderStream::CreateRenderStream();

      for(RenderStream::MaterialInfo& mb:rsptr->GetDrawInfo())
      {
        //部分类不完善，暂时放置延迟渲染
      }
    }
    else
    {
      OnForwardRender(rsptr);
    }
  }

}
