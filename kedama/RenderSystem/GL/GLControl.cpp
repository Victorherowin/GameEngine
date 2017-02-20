#include "GLControl.hpp"

#include "SDLWindow.hpp"
#include "GLForwardRenderer.hpp"
#include "GLDeferredRenderer.hpp"
#include "GLPostProcessor.hpp"
#include "GBuffer.hpp"
#include "../../Log.hpp"

#include "sstream"

namespace Kedama {
  namespace GL {
    GLControl::GLControl()
    {
      m_window=new SDLWindow(this);
    }

    GLControl::~GLControl()
    {
      if(m_gbuffer)delete m_gbuffer;
      if(m_camera_ubo)
      {
        glUnmapNamedBuffer(m_camera_ubo);
        glDeleteBuffers(1,&m_camera_ubo);
      }
      if(m_directional_lights_ubo)
      {
        glUnmapNamedBuffer(m_directional_lights_ubo);
        glDeleteBuffers(1,&m_directional_lights_ubo);
      }
      if(m_point_lights_ubo)
      {
        glUnmapNamedBuffer(m_point_lights_ubo);
        glDeleteBuffers(1,&m_point_lights_ubo);
      }
      if(m_spot_lights_ubo)
      {
        glUnmapNamedBuffer(m_spot_lights_ubo);
        glDeleteBuffers(1,&m_spot_lights_ubo);
      }
      if(m_forward_renderer)delete m_forward_renderer;
      if(m_deferrf_renderer)delete m_deferrf_renderer;
      if(m_post_processor)delete m_post_processor;
      if(m_glcontext)SDL_GL_DeleteContext(m_glcontext);
      delete m_window;
    }

    void GLControl::InitGL()
    {
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
      SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
      SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
      SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
      SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
      SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE,8);
      SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
#ifdef DEBUG
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS,SDL_GL_CONTEXT_DEBUG_FLAG);
#endif

      m_glcontext=SDL_GL_CreateContext(m_window->GetNativePtr());
      glewInit();
      glClearColor(0.4f,0.6f,0.8f,1.0f);
      glClearDepth(0.0f);
 //     glEnable(GL_DEPTH_TEST);
 //     glDepthFunc(GL_LESS);
     // glEnable(GL_CULL_FACE);
   //   glCullFace(GL_BACK);

#ifdef DEBUG
      glDebugMessageCallback(&GLControl::DebugOutput,nullptr);
      glDebugMessageControl(GL_DEBUG_SOURCE_API,GL_DEBUG_TYPE_ERROR,GL_DEBUG_SEVERITY_HIGH,0, nullptr, GL_TRUE);
#endif

      m_forward_renderer=new GLForwardRenderer(this);
      m_deferrf_renderer=new GLDeferredRenderer(this);
      m_post_processor=new GLPostProcessor(this);
      int32_t w,h;
      m_window->GetSize(&w,&h);
      m_gbuffer=new GBuffer();

      //Light UBO
      glCreateBuffers(1,&m_directional_lights_ubo);
      glCreateBuffers(1,&m_point_lights_ubo);
      glCreateBuffers(1,&m_spot_lights_ubo);
      glNamedBufferStorage(m_point_lights_ubo,516,nullptr,GL_MAP_WRITE_BIT|GL_MAP_PERSISTENT_BIT|GL_MAP_COHERENT_BIT);
      glNamedBufferStorage(m_directional_lights_ubo,132,nullptr,GL_MAP_WRITE_BIT|GL_MAP_PERSISTENT_BIT|GL_MAP_COHERENT_BIT);
      glNamedBufferStorage(m_spot_lights_ubo,772,nullptr,GL_MAP_WRITE_BIT|GL_MAP_PERSISTENT_BIT|GL_MAP_COHERENT_BIT);
      m_point_lights_ubo_data=(GLubyte*)glMapNamedBufferRange(m_point_lights_ubo,0,516,GL_MAP_WRITE_BIT|GL_MAP_PERSISTENT_BIT|GL_MAP_COHERENT_BIT);
      m_directional_lights_ubo_data=(GLubyte*)glMapNamedBufferRange(m_directional_lights_ubo,0,132,GL_MAP_WRITE_BIT|GL_MAP_PERSISTENT_BIT|GL_MAP_COHERENT_BIT);
      m_spot_lights_ubo_data=(GLubyte*)glMapNamedBufferRange(m_spot_lights_ubo,0,772,GL_MAP_WRITE_BIT|GL_MAP_PERSISTENT_BIT|GL_MAP_COHERENT_BIT);

      //Creame UBO
      glCreateBuffers(1,&m_camera_ubo);
      glNamedBufferStorage(m_camera_ubo,sizeof(mat4)*3,nullptr,GL_MAP_WRITE_BIT|GL_MAP_PERSISTENT_BIT|GL_MAP_COHERENT_BIT);
      m_camera_ubo_data=(GLubyte*)glMapNamedBufferRange(m_camera_ubo,0,sizeof(mat4)*3,GL_MAP_WRITE_BIT|GL_MAP_PERSISTENT_BIT|GL_MAP_COHERENT_BIT);

      }

    /// \brief
    /// std430
    /// layout(std140,binding=3)uniform DirectionalLights
    /// {
    ///   int num;//0
    ///   vec3 directional[4];//4
    ///   vec4 light_color[4];//68
    /// }
    ///
    /// layout(std140,binding=4)uniform PointLights
    /// {
    ///   int num;//0
    ///   vec3 postion[16];//4
    ///   vec4 light_color[16];//260
    /// }
    ///
    /// layout(std140,binding=5)uniform Spotlights
    /// {
    ///   int num;
    ///   vec3 postion[16];
    ///   vec4 light_color[16];
    ///   float radius[16];//516
    /// }
    void GLControl::SetLights(vector<Light *> &lights)
    {
      m_lights=lights;
      if(m_point_lights_ubo==0||m_directional_lights_ubo==0||m_spot_lights_ubo==0)throw runtime_error("GL No Init");
      GLint num[3]={0,0,0};
      vector<vec3> position[3];
      vector<vec4> color[3];
      vector<float> radius;

      for(Light* light:lights)
      {
        int type=(int)light->GetType();
        position[type].push_back(light->GetTansform()->GetWorldPosition());
        color[type].push_back(light->GetColor());
        ++num[type];
        if(light->GetType()==LightType::SpotLight)
        {
          SpotLight* sl=static_cast<SpotLight*>(light);
          radius.push_back(sl->GetRadius());
        }
      }
      memcpy(m_directional_lights_ubo_data,&num[(int)LightType::PointLight],sizeof(GLint));
      memcpy(m_point_lights_ubo_data,&num[(int)LightType::PointLight],sizeof(GLint));
      memcpy(m_spot_lights_ubo_data,&num[(int)LightType::SpotLight],sizeof(GLint));

      memcpy(m_directional_lights_ubo_data+4,position[(int)LightType::DirectionalLight].data(),position[(int)LightType::DirectionalLight].size()*sizeof(vec3));
      memcpy(m_point_lights_ubo_data+4,position[(int)LightType::PointLight].data(),position[(int)LightType::PointLight].size()*sizeof(vec3));
      memcpy(m_spot_lights_ubo_data+4,position[(int)LightType::SpotLight].data(),position[(int)LightType::SpotLight].size()*sizeof(vec3));

      memcpy(m_directional_lights_ubo_data+68,color[(int)LightType::DirectionalLight].data(),color[(int)LightType::DirectionalLight].size()*sizeof(vec4));
      memcpy(m_point_lights_ubo_data+260,color[(int)LightType::PointLight].data(),color[(int)LightType::PointLight].size()*sizeof(vec4));
      memcpy(m_spot_lights_ubo_data+260,color[(int)LightType::SpotLight].data(),color[(int)LightType::SpotLight].size()*sizeof(vec4));

      vec4* tmp=(vec4*)(m_spot_lights_ubo_data+516);
      for(auto f:radius)
        tmp++->x=f;
    }

    /// \brief
    /// std140
    /// layout(std140,binding=1)uniform Camera
    /// {
    ///    mat4 view_matrix;
    ///    mat4 projection_matrix;
    ///    mat4 view_projection_matrix;
    /// }
    void GLControl::SetCamera(Camera *camera)
    {
      mat4* tmp=(mat4*)m_camera_ubo_data;
      memcpy(tmp,glm::value_ptr(camera->GetViewMatrix()),sizeof(mat4));
      memcpy(tmp+1,glm::value_ptr(camera->GetProjectionMatrix()),sizeof(mat4));
      memcpy(tmp+2,glm::value_ptr(camera->GetProjectionMatrix()*camera->GetViewMatrix()),sizeof(mat4));
    }

    void GLControl::ClearColor(glm::vec4 color)
    {
      glClearColor(color.r,color.g,color.b,color.a);
    }

    void GLControl::ClearAccum(glm::vec4 accum)
    {
      glClearAccum(accum.r,accum.g,accum.b,accum.a);
    }

    void GLControl::ClearDepth(float depth)
    {
      glClearDepth(depth);
    }

    void GLControl::ClearStencil(int32_t s)
    {
      glClearStencil(s);
    }

    void GLControl::Clear(int32_t bit)
    {
      GLenum clearbit=0;
      if(bit&ClearBufferBit::COLOR_BUFFER)
        clearbit|=GL_COLOR_BUFFER_BIT;
      if(bit&ClearBufferBit::DEPTH_BUFFER)
        clearbit|=GL_DEPTH_BUFFER_BIT;
      if(bit&ClearBufferBit::STENCIL_BUFFER)
        clearbit|=GL_STENCIL_BUFFER_BIT;
      if(bit&ClearBufferBit::ACCUM_BUFFER)
        clearbit|=GL_ACCUM_BUFFER_BIT;

      glClear(clearbit);
    }

    void GLControl::Present()
    {
      SDL_GL_SwapWindow(m_window->GetNativePtr());
    }

    IWindow* GLControl::GetWindow()
    {
      return m_window;
    }

    IForwardRenderer* GLControl::GetForwardRenderer()
    {
      return m_forward_renderer;
    }

    IDeferredRenderer* GLControl::GetDeferredRenderer()
    {
      return m_deferrf_renderer;
    }

    IPostProcessor* GLControl::GetPostProcessor()
    {
      return m_post_processor;
    }

#ifdef DEBUG
    void GLControl::DebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message,const void *userParam)
    {
      // 忽略一些不重要的错误/警告代码
      if(id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

      stringstream ss;

      ss << "---------------" << std::endl;
      ss << "Debug message (" << id << "): " <<  message << std::endl;

      switch (source)
      {
        case GL_DEBUG_SOURCE_API:             ss << "Source: API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   ss << "Source: Window System"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: ss << "Source: Shader Compiler"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:     ss << "Source: Third Party"; break;
        case GL_DEBUG_SOURCE_APPLICATION:     ss << "Source: Application"; break;
        case GL_DEBUG_SOURCE_OTHER:           ss << "Source: Other"; break;
      } ss << std::endl;

      switch (type)
      {
        case GL_DEBUG_TYPE_ERROR:               ss << "Type: Error"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: ss << "Type: Deprecated Behaviour"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  ss << "Type: Undefined Behaviour"; break;
        case GL_DEBUG_TYPE_PORTABILITY:         ss << "Type: Portability"; break;
        case GL_DEBUG_TYPE_PERFORMANCE:         ss << "Type: Performance"; break;
        case GL_DEBUG_TYPE_MARKER:              ss << "Type: Marker"; break;
        case GL_DEBUG_TYPE_PUSH_GROUP:          ss << "Type: Push Group"; break;
        case GL_DEBUG_TYPE_POP_GROUP:           ss << "Type: Pop Group"; break;
        case GL_DEBUG_TYPE_OTHER:               ss << "Type: Other"; break;
      } ss << std::endl;

      switch (severity)
      {
        case GL_DEBUG_SEVERITY_HIGH:         ss << "Severity: high"; break;
        case GL_DEBUG_SEVERITY_MEDIUM:       ss << "Severity: medium"; break;
        case GL_DEBUG_SEVERITY_LOW:          ss << "Severity: low"; break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: ss << "Severity: notification"; break;
      } ss << std::endl;
      ss << std::endl;
      KEDAMALOGE(ss.str().c_str());
    }
#endif
  }
}
