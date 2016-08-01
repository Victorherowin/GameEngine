#ifndef MESH
#define MESH

#include "Vertex.hpp"
#include "Material.hpp"
#include "../Config.hpp"
#include "RenderStream.hpp"



namespace Kedama
{

  class KEDAMA_API StaticModel
  {
  public:
    explicit StaticModel(RenderStreamPtr& rs);
    void SetRenderStream(RenderStreamPtr& rs);
    const RenderStreamPtr& GetRenderStream();

  private:
    RenderStreamPtr m_rs;
  };

  class KEDAMA_API DynamicModel
  {
  public:
    void SetRenderStream(RenderStreamPtr& rs);
    const RenderStreamPtr& GetRenderStream();

  private:
    RenderStreamPtr m_rs;
  };
}

#endif
