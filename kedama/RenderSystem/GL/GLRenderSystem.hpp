#ifndef GLRENDERSYSTEM
#define GLRENDERSYSTEM

#include "../IRenderSystem.hpp"
#include "SDLWindow.hpp"


namespace Kedama
{
  class GLRenderSystem:public IRenderSystem
  {
  public:
    void Init()override;
    void Quit()override;

    void SetCamera(CameraPtr camera)override;
    void Clear()override;
    void Flush()override;
    void SwapBuffer()override;

    void OnRender(RenderStreamPtr)override;

    IShader* CreateShader(const std::string shader_src)override;
    const string GetShaderLanguage()override;

    IWindow* GetWindow()override;

  private:
    CameraPtr m_main_camera;

    SDLWindow m_win;
    SDL_GLContext m_gl;
  };
}

#endif
