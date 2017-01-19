#include "FrameBuffer.hpp"

namespace Kedama
{
  void FrameBuffer::Create(uint32_t w, uint32_t h)
  {
    m_w=w;
    m_h=h;
  }

  void FrameBuffer::Attach(AttachType type)
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

  void FrameBuffer::RemoveAttach(AttachType type)
  {
    for(auto it=m_attachs.begin();it!=m_attachs.end();++it)
    {
      if(*it==type)
      {
        OnRemove(*it);
        m_attachs.erase(it);
      }
    }
  }

  void FrameBuffer::RemoveAll()
  {
    for(auto it=m_attachs.begin();it!=m_attachs.end();++it)
    {
      OnRemove(*it);
      it=m_attachs.erase(it);
    }
  }

}
