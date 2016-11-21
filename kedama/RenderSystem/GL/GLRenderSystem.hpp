#ifndef GLRENDERSYSTEM
#define GLRENDERSYSTEM

#include "../RenderSystem.hpp"
#include "SDLWindow.hpp"

#include "VAOManager.hpp"
#include "UBOModelMatrixManager.hpp"


namespace Kedama
{
  class GLRenderSystem:public RenderSystem
  {
  public:
    GLRenderSystem();
    void SetCamera(const CameraPtr& camera)override;
    void SetViewport(Viewport* vp)override;

    void Init()override;
    void Quit()override;

    void Clear()override;
    void Flush()override;
    void SwapBuffer()override;

    void OnForwardRender(const RenderStreamPtr&)override;
    void OnDeferredRender(const RenderStreamPtr&)override;

    const string GetShaderLanguage()override;

    IWindow* GetWindow()override;
  private:
    GLuint SetupVAO(VertexBufferPtr pvbo);

  private:
    SDLWindow m_win;
    SDL_GLContext m_gl;

    VAOManager m_vao_manager;
    GLuint m_model_view_ubo;
  };
}

#endif
