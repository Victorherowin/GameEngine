#ifndef MESH
#define MESH

#include "../RenderSystem/Vertex.hpp"
#include "../RenderSystem/Material.hpp"
#include "../Config.hpp"
#include "../RenderSystem/RenderStream.hpp"
#include "GameObject.hpp"


namespace Kedama
{

  class KEDAMA_API StaticModel:public GameObject
  {
  public:
    explicit StaticModel(const string& name);
    void SetRenderStream(RenderStreamPtr& rs);

    inline const RenderStreamPtr& GetRenderStream(){return m_rs;}

    void AddMesh(const RenderStream::MeshBuffer &mb,MaterialPtr& material);

  private:
    RenderStreamPtr m_rs;
    vector<uint32_t> m_mesh_ids;
  };

  class KEDAMA_API DynamicModel:public GameObject
  {
  public:
    void SetRenderStream(RenderStreamPtr& rs);
    const RenderStreamPtr& GetRenderStream();

  private:
    RenderStreamPtr m_rs;
  };
}

#endif
