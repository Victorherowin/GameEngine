#include "RenderSystem.hpp"
#include "../Engine.hpp"

#include "Interface/IForwardRenderer.hpp"
#include "Interface/IDeferredRenderer.hpp"
#include "Interface/IControl.hpp"
#include "Interface/IPostProcessor.hpp"

#include "CommandBuffer.hpp"

namespace Kedama
{
  RenderSystem::RenderSystem(IRendererFactory *factory)
  {
    m_control=factory->GetControl();
  }

  IWindow* RenderSystem::GetWindow()
  {
    return m_control->GetWindow();
  }

  void RenderSystem::Clear()
  {
    m_control->Clear(ClearBufferBit::COLOR_BUFFER|ClearBufferBit::DEPTH_BUFFER);
  }

  void RenderSystem::SwapBuffer()
  {
    m_control->Present();
  }

  void RenderSystem::SetCamera(Camera* camera)
  {
    m_main_camera=camera;
  }

  void RenderSystem::SetLights(vector<Light*>& lights)
  {
    m_lights=lights;
  }

  void RenderSystem::Render(CommandBuffer &cb)
  {
    //检查
    if(m_control->GetForwardRenderer()!=nullptr)
      m_forward_renderer=m_control->GetForwardRenderer();
    else throw runtime_error("No Window");

    if(m_control->GetPostProcessor()!=nullptr)
      m_post_processor=m_control->GetPostProcessor();
    else throw runtime_error("No Window");

    if(m_control->GetDeferredRenderer()!=nullptr)
      m_deferred_renderer=m_control->GetDeferredRenderer();

    if(m_use_deferred_render==true&&m_deferred_renderer==nullptr)
      throw runtime_error("No Implement Deferred Renderer");

    if(m_main_camera)
      cb.Sort(m_main_camera);
    else
      throw runtime_error("No Camera!");

    m_control->SetCamera(m_main_camera);
    m_control->SetLights(m_lights);

    //渲染阴影贴图

    if(cb.GetDeferredCommands().size()>0)
    {
      for(auto& rc:cb.GetDeferredCommands())
        m_forward_renderer->RenderShadow(rc);
    }

    if(cb.GetMergedRenderCommans().size()>0)
    {
      for(auto& mrc:cb.GetMergedRenderCommans())
        m_forward_renderer->RenderShadow(mrc);
    }

    if(cb.GetForwardCommands().size()>0)
    {
      for(auto& rc:cb.GetForwardCommands())
        m_forward_renderer->RenderShadow(rc);
    }

    //透明物体不生成阴影
    /*  if(cb.GetAlphaForwardCommands().size()>0)
      {
        for(auto& rc:cb.GetAlphaForwardCommands())
          m_forward_renderer->RenderShadow(rc);
      }*/

    if(m_use_deferred_render)
    {
      //渲染
      if(cb.GetDeferredCommands().size()>0)
      {
        for(auto& rc:cb.GetDeferredCommands())
          m_deferred_renderer->Render(rc);
      }

      if(cb.GetMergedRenderCommans().size()>0)
      {
        for(auto& mrc:cb.GetMergedRenderCommans())
          m_deferred_renderer->Render(mrc);
      }

      m_deferred_renderer->Finish();

      if(cb.GetForwardCommands().size()>0)
      {
        for(auto& rc:cb.GetForwardCommands())
          m_forward_renderer->Render(rc);
      }

      if(cb.GetAlphaForwardCommands().size()>0)
      {
        for(auto& rc:cb.GetAlphaForwardCommands())
          m_forward_renderer->Render(rc);
      }
    }
    else
    {
      //渲染
      if(cb.GetDeferredCommands().size()>0)
      {
        for(auto& rc:cb.GetDeferredCommands())
          m_forward_renderer->Render(rc);
      }

      if(cb.GetForwardCommands().size()>0)
      {
        for(auto& rc:cb.GetForwardCommands())
          m_forward_renderer->Render(rc);
      }

      if(cb.GetMergedRenderCommans().size()>0)
      {
        for(auto& mrc:cb.GetMergedRenderCommans())
          m_forward_renderer->Render(mrc);
      }

      if(cb.GetAlphaForwardCommands().size()>0)
      {
        for(auto& rc:cb.GetAlphaForwardCommands())
          m_forward_renderer->Render(rc);
      }
    }

    //后处理
    if(cb.GetPostProcessCommands().size()>0)
    {
      for(auto& ppc:cb.GetPostProcessCommands())
        m_post_processor->PostProcess(ppc);
    }
  }

}
