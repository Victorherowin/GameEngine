#include "Mesh.hpp"

#include "../Engine.hpp"

namespace Kedama
{
  StaticModel::StaticModel(const string& name):GameObject(name)
  {
    m_rs=Engine::GetSingleton().GetRenderSystemFactory()->CreateRenderStream();
  }

  void StaticModel::SetRenderStream(RenderStreamPtr& rs)
  {
    m_rs=rs;
  }

  void DynamicModel::SetRenderStream(RenderStreamPtr& rs)
  {
    m_rs=rs;
  }

  const RenderStreamPtr& DynamicModel::GetRenderStream()
  {
    return m_rs;
  }

  void StaticModel::AddMesh(const RenderStream::MeshBuffer &mb,MaterialPtr& material)
  {
    m_mesh_ids.push_back(m_rs->AddMeshBuffer(mb));
    m_rs->BindMaterial(m_mesh_ids.back(),material,0);
    m_rs->GetInstancingInfoRef(m_mesh_ids.back()).AddInstance(GetTansform());
  }
}
