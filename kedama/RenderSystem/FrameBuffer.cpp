#include "FrameBuffer.hpp"

namespace Kedama
{
  void FrameBuffer::AddTexture2D(ITexture2DPtr texture,AttachType attachment,int32_t attachment_id,int32_t level)
  {
    m_texs.push_back(texture);
  }
}
