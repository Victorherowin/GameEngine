/*!
  \file RenderSystem.hpp
  \brief 分发渲染对象，以及后处理

  \date 2017.01.31
  \author KedamaOvO
*/


#ifndef _H_RENDERSYSTEM_
#define _H_RENDERSYSTEM_

#include <string>

#include "../GameObject/GameObjectClass.hpp"
#include "RenderSystemClass.hpp"

#include "../Define.hpp"
#include "../Include.hpp"

namespace Kedama
{
  using std::string;
  class IRendererFactory;

  class RenderSystem
  {
  public:
    RenderSystem(IRendererFactory* factory);
    ~RenderSystem(){}
    void UseDeferredRender(bool use);
    void SetCamera(Camera* camera);

    void Render(CommandBuffer& cb);
    void Clear();
    void SwapBuffer();

    IWindow* GetWindow();

  private:
    IForwardRenderer* m_forward_renderer=nullptr;
    IDeferredRenderer* m_deferred_renderer=nullptr;
    IPostProcessor* m_post_processor=nullptr;
    IControl* m_control=nullptr;

    Camera* m_main_camera=nullptr;

    bool m_use_deferred_render=false;
  };
}

#endif
