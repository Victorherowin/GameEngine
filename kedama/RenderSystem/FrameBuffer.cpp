#include "FrameBuffer.hpp"

namespace Kedama
{
  void FrameBuffer::Create(uint32_t w, uint32_t h)
  {
    m_w=w;
    m_h=h;
  }

  void FrameBuffer::AddAttach(AttachType type)
  {
    for(AttachType t:m_attachs)
    {
      if(t==type)
      {
        throw std::runtime_error("This Attach Point exists");
      }
    }
    m_attachs.push_back(type);
    OnAttach(type);
  }

}
