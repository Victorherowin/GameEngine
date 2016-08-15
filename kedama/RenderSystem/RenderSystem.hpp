#ifndef RENDERSYSTEM
#define RENDERSYSTEM

#include <string>
#include "../GameObject/GameObject.hpp"
#include "ITexture2D.hpp"
#include "IShader.hpp"
#include "../IWindow.hpp"
#include "../GameObject/Mesh.hpp"
#include "RenderStream.hpp"
#include "../GameObject/Camera.hpp"

#include "../Config.hpp"

namespace Kedama
{
  using std::string;

  class RenderSystem
  {
  public:
    virtual ~RenderSystem(){}

    void Render(const RenderStreamPtr&);
    void UseDeferredRender(bool use);
    void SetCamera(CameraPtr camera);

    virtual void Init()=0;
    virtual void Quit()=0;
    virtual IWindow* GetWindow()=0;

    virtual void Clear()=0;
    virtual void Flush()=0;
    virtual void SwapBuffer()=0;

  protected:
    virtual void OnForwardRender(const RenderStreamPtr& rsptr)=0;
    virtual void OnDeferredRender(const RenderStreamPtr&){throw std::runtime_error(string("No Implement DeferredRender！"));}

    virtual const string GetShaderLanguage()=0;

  protected:
    CameraPtr m_main_camera=nullptr;
    bool m_use_deferred_render;

  };
}

#endif
