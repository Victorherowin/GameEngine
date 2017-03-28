#include "Mesh.hpp"
#include "../Engine.hpp"
namespace Kedama {
  Mesh::Mesh()
  {
    m_native=Engine::GetSingleton().GetRendererFactory()->CreateMeshNative();
  }

  Mesh::~Mesh()
  {
    delete m_native;
  }

  void Mesh::SetVertices(vector<vec3>& vertices)
  {
    m_vertices=vertices;
    m_native->UploadVertices(m_vertices);
  }

  void Mesh::SetIndices(vector<uint32_t>& indices)
  {
    m_indices=indices;
    m_native->UploadIndices(m_indices);
  }

  void Mesh::SetUVs(vector<vec2>& uvs)
  {
    m_uvs=uvs;
    m_native->UploadUVs(m_uvs);
  }

  void Mesh::SetNormals(vector<vec3>& normals)
  {
    m_normals=normals;
    m_native->UploadNormals(m_normals);
  }

  void Mesh::SetTangents(vector<vec3>& tangent)
  {
    m_tangent=tangent;
    m_native->UploadTangents(m_tangent);
  }
}
