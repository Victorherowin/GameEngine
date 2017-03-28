#ifndef _H_GLCONTROL
#define _H_GLCONTROL

#include "GLRenderSystemClass.hpp"
#include "GBuffer.hpp"
#include "../Interface/IControl.hpp"
#include <GL/glew.h>
#include <SDL2/SDL.h>

namespace Kedama {
  namespace GL{

    class GLControl:public IControl
    {
    public:
      GLControl();
      ~GLControl();

      void SetLights(vector<Light*>& lights)override;
      void SetCamera(Camera* camera)override;
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

	  inline const vector<Light*>& GetLights() { return m_lights; }
      inline const unique_ptr<GBuffer>& GetGBuffer() { return m_gbuffer; }
      inline GLuint GetCameraUBO(){return m_camera_ubo;}

    private:
#ifdef DEBUG
      static void GLAPIENTRY DebugOutput(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);
#endif
    private:
      SDLWindow* m_window=nullptr;
      GLForwardRenderer* m_forward_renderer=nullptr;
      GLDeferredRenderer* m_deferrf_renderer=nullptr;
      GLPostProcessor* m_post_processor=nullptr;

      //UBO Area
      GLuint m_camera_ubo=0;
      GLubyte* m_camera_ubo_data=nullptr;

	  vector<Light*> m_lights;

      unique_ptr<GBuffer> m_gbuffer=nullptr;

      SDL_GLContext m_glcontext=nullptr;
    };
  }
}

#endif
