#include "RenderStream.hpp"

namespace Kedama
{
  uint32_t RenderStream::AddMeshBuffer(MeshBuffer mb)
  {
    m_meshbuffers.push_back(mb);
    return m_meshbuffers.end()-m_meshbuffers.begin()-1;
  }

  void RenderStream::BindMaterial(uint32_t mesh_id, MaterialPtr &tex, uint32_t offset, uint32_t size)
  {
    MaterialInfo info;
    info.mb=m_meshbuffers[mesh_id];
    info.offset=offset;
    info.vertex_size=size;
    info.tex=tex;

    m_texs.push_back(info);
  }

  RenderStreamPtr RenderStream::CreateRenderStream()
  {
    return std::make_shared<RenderStream>();
  }

  void RenderStream::Clear()
  {
    m_meshbuffers.clear();
    m_texs.clear();
  }
}
