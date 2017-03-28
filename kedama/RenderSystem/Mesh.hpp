#ifndef _H_MESH
#define _H_MESH

#include "../Define.hpp"
#include "../Include.hpp"
#include "../GLMInclude.hpp"
#include "Material.hpp"

namespace Kedama
{
  using namespace glm;
  using namespace std;
  class Mesh
  {
  public:
    class INative;
  public:
    Mesh();
    ~Mesh();

    void SetVertices(vector<vec3>& vertices);
    void SetIndices(vector<uint32_t>& indices);
    void SetUVs(vector<vec2>& uvs);
    void SetNormals(vector<vec3>& normals);
    void SetTangents(vector<vec3>& tangent);

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

    inline const INative* GetNativePtr()const
    {return m_native;}
  private:
    vector<vec2> m_uvs;
    vector<vec3> m_vertices;
    vector<vec3> m_normals;
    vector<vec3> m_tangent;
    vector<uint32_t> m_indices;
    INative* m_native;
  };

  class KEDAMA_API Mesh::INative
  {
  public:
    ~INative(){}
    virtual void UploadVertices(const vector<vec3>& vertices)=0;
    virtual void UploadIndices(const vector<uint32_t>& indices)=0;
    virtual void UploadNormals(const vector<vec3>& normals)=0;
    virtual void UploadUVs(const vector<vec2>& uvs)=0;
    virtual void UploadTangents(const vector<vec3>& tangents)=0;
  };
}

#endif
