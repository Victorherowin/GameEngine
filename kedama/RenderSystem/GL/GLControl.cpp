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
      glDebugMessageCallback(&GLControl::DebugOutput,nullptr);
      glDebugMessageControl(GL_DEBUG_SOURCE_API,GL_DEBUG_TYPE_ERROR,GL_DEBUG_SEVERITY_HIGH,0, nullptr, GL_TRUE);
#endif

      m_glcontext=SDL_GL_CreateContext(m_window->GetNativePtr());
      glewInit();

      m_forward_renderer=new GLForwardRenderer(this);
      m_deferrf_renderer=new GLDeferredRenderer(this);
      m_post_processor=new GLPostProcessor(this);
      int32_t w,h;
      m_window->GetSize(&w,&h);
      m_gbuffer=new GBuffer(w,h);
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
