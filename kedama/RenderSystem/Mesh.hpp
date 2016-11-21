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
  DEFINE_SHARED_PTR(BaseModel)
  DEFINE_SHARED_PTR(DynamicModel)

  using MeshBuffer=pair<VertexBufferPtr,IIndexBufferPtr>;

  struct Mesh
  {
    MeshBuffer mesh_buffer;
    MaterialPtr material;
    uint32_t offset;
  };

  class KEDAMA_API BaseModel:public GameObject
  {
  public:
    BaseModel(const string& name="");

    inline const list<Mesh>& GetMeshes(){return m_meshs;}
    void AddMesh(const Mesh &mb,MaterialPtr& material,uint32_t offset=0);

    static BaseModelPtr CreateBaseModel(const string& name);

  protected:
    list<Mesh> m_meshs;
  };

  class KEDAMA_API DynamicModel:public BaseModel
  {
  public:
    DynamicModel(const string& name=string());
    static DynamicModelPtr CreateDynamicModel(const string& name);

  private:
    //AABBBox
  };
}

#endif
