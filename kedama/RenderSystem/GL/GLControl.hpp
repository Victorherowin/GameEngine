#ifndef _H_GLCONTROL
#define _H_GLCONTROL

#include "GLRenderSystemClass.hpp"
#include "../Interface/IControl.hpp"
#include <GL/glew.h>
#include <SDL.h>

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

      inline GBuffer& GetGBuffer();
      inline GLuint GetDirectionalLightsUBO(){return m_directional_lights_ubo;}
      inline GLuint GetPointLightsUBO(){return m_point_lights_ubo;}
      inline GLuint GetSpotLightsUBO(){return m_spot_lights_ubo;}
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

      GLuint m_directional_lights_ubo=0;
      GLuint m_point_lights_ubo=0;
      GLuint m_spot_lights_ubo=0;

      GLubyte* m_directional_lights_ubo_data=nullptr;
      GLubyte* m_point_lights_ubo_data=nullptr;
      GLubyte* m_spot_lights_ubo_data=nullptr;

      vector<Light*> m_lights;

      GBuffer* m_gbuffer=nullptr;

      SDL_GLContext m_glcontext=nullptr;
    };
  }
}

#endif
