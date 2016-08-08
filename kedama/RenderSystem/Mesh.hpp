#ifndef MESH
#define MESH

#include "Vertex.hpp"
#include "Material.hpp"
#include "../Config.hpp"
#include "RenderStream.hpp"
#include "../GameObject.hpp"


namespace Kedama
{

  class KEDAMA_API StaticModel:public GameObject
  {
  public:
    explicit StaticModel(const string& name);
    void SetRenderStream(RenderStreamPtr& rs);
    const RenderStreamPtr& GetRenderStream();

  private:
    RenderStreamPtr m_rs;
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
