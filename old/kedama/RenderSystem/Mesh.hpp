#ifndef MESH
#define MESH

#include "../Include.hpp"
#include "../Define.hpp"
#include "../GameObject/GameObject.hpp"

#include "VertexBuffer.hpp"
#include "IIndexBuffer.hpp"
#include "Vertex.hpp"
#include "Material.hpp"

namespace Kedama
{
  struct Mesh
  {
    VertexBuffer* vbo;
    IIndexBuffer* ibo;
    Material* material;
    uint32_t offset;
  };

  class KEDAMA_API BaseModel:public GameObject
  {
  public:
    BaseModel(const string& name="");

    inline const list<Mesh>& GetMeshes(){return m_meshs;}
    void AddMesh(Mesh &mb);

    static BaseModel* CreateBaseModel(const string& name);

  protected:
    list<Mesh> m_meshs;
  };

  class KEDAMA_API DynamicModel:public BaseModel
  {
  public:
    DynamicModel(const string& name=string());
    static DynamicModel* CreateDynamicModel(const string& name);

  private:
    //AABBBox
  };
}

#endif
