#ifndef _H_MESH
#define _H_MESH

#include "../Include.hpp"
#include "Material.hpp"

namespace Kedama
{
  using namespace glm;
  using namespace std;
  class Mesh
  {
  public:
    class Native;
  //TODO 顶点 UVs TBN...
  public:
    Mesh();
    ~Mesh();

    inline void SetVertices(vector<vec3>& vertices)
    {m_vertices=vertices;}

    inline void SetIndices(vector<uint32_t>& indices)
    {m_indices=indices;}

    inline void SetUVs(vector<vec2>& uvs)
    {m_uvs=uvs;}

    inline void SetNormal(vector<vec3>& normals)
    {m_normals=normals;}

    inline void SetTangent(vector<vec3>& tangent)
    {m_tangent=tangent;}

    inline vector<vec3>& GetVertices()
    {return m_vertices;}

    inline vector<uint32_t>& GetIndices()
    {return m_indices;}

    inline vector<vec2>& GetUVs()
    {return m_uvs;}

    inline vector<vec3>& GetNormal()
    {return m_normals;}

    inline vector<vec3>& GetTangent()
    {return m_tangent;}

  private:
    vector<vec2> m_uvs;
    vector<vec3> m_vertices;
    vector<vec3> m_normals;
    vector<vec3> m_tangent;
    vector<uint32_t> m_indices;
    Material* m_material;
    Native* m_native;
  };

  class Mesh::Native
  {
  public:
    ~Native(){}
    void SetMesh(Mesh* mesh);
    Mesh* GetMesh();

    virtual void Upload()=0;
  protected:
    Mesh* m_mesh=nullptr;
  };
}

#endif
