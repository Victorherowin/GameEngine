#ifndef GLRENDERSYSTEM
#define GLRENDERSYSTEM

#include "../RenderSystem.hpp"
#include "SDLWindow.hpp"


namespace Kedama
{
  class GLRenderSystem:public RenderSystem
  {
  public:
    void Init()override;
    void Quit()override;

    void Clear()override;
    void Flush()override;
    void SwapBuffer()override;

    void OnForwardRender(RenderStreamPtr&)override;
    void OnDeferredRender(RenderStreamPtr&)override;

    const string GetShaderLanguage()override;

    IWindow* GetWindow()override;

  private:

    SDLWindow m_win;
    SDL_GLContext m_gl;
  };
}

#endif
