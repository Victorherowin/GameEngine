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
    class INative;
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

    inline void SetNormals(vector<vec3>& normals)
    {m_normals=normals;}

    inline void SetTangents(vector<vec3>& tangent)
    {m_tangent=tangent;}

    inline const vector<vec3>& GetVertices()const
    {return m_vertices;}

    inline const vector<uint32_t>& GetIndices()const
    {return m_indices;}

    inline const vector<vec2>& GetUVs()const
    {return m_uvs;}

    inline const vector<vec3>& GetNormals()const
    {return m_normals;}

    inline const vector<vec3>& GetTangents()const
    {return m_tangent;}

  private:
    vector<vec2> m_uvs;
    vector<vec3> m_vertices;
    vector<vec3> m_normals;
    vector<vec3> m_tangent;
    vector<uint32_t> m_indices;
    INative* m_native;
  };

  class Mesh::INative
  {
  public:
    ~INative(){}
    virtual void Upload(const Mesh& mesh)=0;
  };
}

#endif
