#ifndef GLFRAMEBUFFER
#define GLFRAMEBUFFER

#include "GLTexture2D.hpp"

#include "../FrameBuffer.hpp"

#include "../../Include.hpp"
#include "../../Define.hpp"

namespace Kedama
{
  class GLFrameBuffer:public FrameBuffer
  {
  public:
    GLFrameBuffer();
    ~GLFrameBuffer();

    inline list<pair<AttachType,GLTexture2D*>>& GetGLTextureObjs(){return m_texs;}
    inline list<pair<AttachType,GLuint>>& GetGLRenderBufferObjs(){return m_rbos;}
    inline GLuint GetObj(){return m_fbo;}

  protected:

    void OnAttach(AttachType type)override;
    void OnRemove(AttachType type)override;

  private:
    GLuint m_fbo;
    list<pair<AttachType,GLTexture2D*>> m_texs;
    list<pair<AttachType,GLuint>> m_rbos;
  };
}

#endif
