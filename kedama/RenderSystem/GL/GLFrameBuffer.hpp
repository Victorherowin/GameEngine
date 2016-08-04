#ifndef GLFRAMEBUFFER
#define GLFRAMEBUFFER

#include "GLTexture2D.hpp"

#include "../FrameBuffer.hpp"

#include "../../Config.hpp"

namespace Kedama
{
  class GLFrameBuffer:public FrameBuffer
  {
  public:
    GLFrameBuffer();
    ~GLFrameBuffer();

  protected:

    void OnAttach(AttachType type)override;

  private:
    GLuint m_fbo;
    vector<GLTexture2D*> m_texs;
    vector<GLuint> m_rbos;

    uint32_t m_w,m_h;
  };
}

#endif
