#ifndef RENDERSYSTEM
#define RENDERSYSTEM

#include <string>

/*#include "ITexture2D.hpp"
#include "Shader.hpp"
#include "RenderTarget.hpp"
#include "Mesh.hpp"
*/
#include "Viewport.hpp"

#include "../IWindow.hpp"

#include "../GameObject/GameObject.hpp"
#include "../GameObject/Camera.hpp"

#include "../Define.hpp"
#include "../Include.hpp"

namespace Kedama
{
  using std::string;

  class RenderSystem
  {
  public:
    virtual ~RenderSystem(){}

  //  void Render(RenderStream*);
    void UseDeferredRender(bool use);
    virtual void SetCamera(Camera* camera);
    virtual void SetViewport(Viewport* vp);

    virtual void Init()=0;
    virtual void Quit()=0;
    virtual IWindow* GetWindow()=0;

    virtual void Clear()=0;
    virtual void Flush()=0;
    virtual void SwapBuffer()=0;

  protected:

//    virtual void OnForwardRender(const RenderStream* rsptr)=0;
//    virtual void OnDeferredRender(const RenderStream*){throw std::runtime_error(string("No Implement DeferredRender！"));}

    virtual const string GetShaderLanguage()=0;

  protected:
//    RenderTarget m_render_target;
    Camera* m_main_camera=nullptr;
    Viewport* m_viewport=nullptr;

    bool m_use_deferred_render;

  };
}

#endif
