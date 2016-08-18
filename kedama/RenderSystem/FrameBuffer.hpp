#ifndef FRAMEBUFFER
#define FRAMEBUFFER

#include "ITexture2D.hpp"

#include "../Config.hpp"

namespace Kedama
{
  enum class AttachType
  {
    COLOR_ATTACHMENT0,
    COLOR_ATTACHMENT1,
    COLOR_ATTACHMENT2,
    COLOR_ATTACHMENT3,
    COLOR_ATTACHMENT4,
    COLOR_ATTACHMENT5,
    COLOR_ATTACHMENT6,
    COLOR_ATTACHMENT7,
    COLOR_ATTACHMENT8,
    COLOR_ATTACHMENT9,
    COLOR_ATTACHMENT10,
    COLOR_ATTACHMENT11,
    COLOR_ATTACHMENT12,
    COLOR_ATTACHMENT13,
    COLOR_ATTACHMENT14,
    COLOR_ATTACHMENT15,
    DEPTH_ATTACHMENT,
    STENCIL_ATTACHMENT,
    DEPTH_STENCIL_ATTACHMENT
  };

  DEFINE_SHARED_PTR(FrameBuffer)

  class FrameBuffer
  {
    public:
    virtual ~FrameBuffer(){}
    void Create(uint32_t w,uint32_t h);
    void Attach(AttachType type);
    void RemoveAttach(AttachType type);
    void RemoveAll();

    protected:
    virtual void OnAttach(AttachType type)=0;
    virtual void OnRemove(AttachType type)=0;
    protected:
    list<AttachType> m_attachs;
    uint32_t m_w,m_h;

  };
}

#endif
