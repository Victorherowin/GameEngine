#include "RenderStream.hpp"

namespace Kedama
{
  uint32_t RenderStream::AddMeshBuffer(const MeshBuffer& mb)
  {
    m_meshbuffers.push_back(mb);
    return m_meshbuffers.end()-m_meshbuffers.begin()-1;
  }

  void RenderStream::BindMaterial(uint32_t mesh_id, MaterialPtr &material, uint32_t offset)
  {
    if(mesh_id>m_meshbuffers.size())
      throw std::runtime_error("Error of Mesh ID");

    MaterialInfo mi({m_meshbuffers[mesh_id],offset,material});
    m_texs.push_back(mi);
    OnBindMaterial(&m_texs.back());
  }

  void RenderStream::Clear()
  {
    m_meshbuffers.clear();
    OnClear();
  }
}
