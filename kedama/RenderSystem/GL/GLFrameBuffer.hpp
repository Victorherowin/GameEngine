#ifndef GLFRAMEBUFFER
#define GLFRAMEBUFFER

#include "GLTexture2D.hpp"

#include "../FrameBuffer.hpp"

#include "../../Config.hpp"

namespace Kedama
{
  DEFINE_SHARED_PTR(GLFrameBuffer)

  class GLFrameBuffer:public FrameBuffer
  {
  public:
    GLFrameBuffer();
    ~GLFrameBuffer();

    inline vector<GLTexture2D*>& GetGLTextureObjs(){return m_texs;}
    inline vector<GLuint>& GetGLRenderBufferObjs(){return m_rbos;}
    inline GLuint GetObj(){return m_fbo;}

  protected:

    void OnAttach(AttachType type)override;

  private:
    GLuint m_fbo;
    vector<GLTexture2D*> m_texs;
    vector<GLuint> m_rbos;
  };
}

#endif
