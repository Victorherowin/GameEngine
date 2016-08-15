#include "RenderSystem.hpp"
#include "../Engine.hpp"

namespace Kedama {

  void RenderSystem::SetCamera(CameraPtr camera)
  {
    m_main_camera=camera;
  }

  void RenderSystem::Render(const RenderStreamPtr& rsptr)
  {
    if(m_use_deferred_render)
    {
      RenderStreamPtr transparent_rs=Engine::GetSingleton().GetRenderSystemFactory()->CreateRenderStream();
      RenderStreamPtr no_transparent_rs=Engine::GetSingleton().GetRenderSystemFactory()->CreateRenderStream();//拆分透明和不透明材质

      for(RenderStream::MeshInfo& mb:rsptr->GetDrawInfo())
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
