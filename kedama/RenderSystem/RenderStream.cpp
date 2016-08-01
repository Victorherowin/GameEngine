#include "RenderStream.hpp"

namespace Kedama
{
  uint32_t RenderStream::AddMeshBuffer(MeshBuffer mb)
  {
    m_meshbuffers.push_back(mb);
    return m_meshbuffers.end()-m_meshbuffers.begin()-1;
  }
}
