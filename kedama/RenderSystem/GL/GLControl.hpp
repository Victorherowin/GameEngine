#ifndef _H_GLCONTROL
#define _H_GLCONTROL

#include "GLRenderSystemClass.hpp"
#include "../Interface/IControl.hpp"
#include "SDL2/SDL.h"

namespace Kedama {
  namespace GL{

    class GLControl:public IControl
    {
    public:
      GLControl();
      ~GLControl();

      void ClearColor(glm::vec4 color)override;
      void ClearDepth(float depth)override;
      void ClearStencil(int32_t s)override;
      void ClearAccum(glm::vec4 accum)override;
      void Clear(int32_t bit)override;
      void Present()override;
      IWindow* GetWindow()override;
      IForwardRenderer* GetForwardRenderer()override;
      IDeferredRenderer* GetDeferredRenderer()override;
      IPostProcessor* GetPostProcessor()override;

      void InitGL();

      inline GBuffer& GetGBuffer();

    private:
#ifdef DEBUG
      static void GLAPIENTRY DebugOutput(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);
#endif

    private:
      SDLWindow* m_window=nullptr;
      GLForwardRenderer* m_forward_renderer=nullptr;
      GLDeferredRenderer* m_deferrf_renderer=nullptr;
      GLPostProcessor* m_post_processor=nullptr;

      GBuffer* m_gbuffer=nullptr;

      SDL_GLContext m_glcontext=nullptr;


    };
  }
}

#endif
