#ifndef GLRENDERSYSTEM
#define GLRENDERSYSTEM

#include "../RenderSystem.hpp"
#include "SDLWindow.hpp"

namespace Kedama
{
  namespace GL
  {
    class GLRenderSystem:public RenderSystem
    {
    public:
      GLRenderSystem();
      void SetCamera(Camera* camera)override;
      void SetViewport(Viewport* vp)override;

      void Init()override;
      void Quit()override;

      void Clear()override;
      void Flush()override;
      void SwapBuffer()override;

      //void OnForwardRender(const RenderStream*)override;
      //void OnDeferredRender(const RenderStream*)override;

      const string GetShaderLanguage()override;

      IWindow* GetWindow()override;
    private:

    private:
      SDLWindow m_win;
      SDL_GLContext m_gl;

      GLuint m_model_view_ubo;
    };
  }
}

#endif
