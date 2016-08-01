#include "Mesh.hpp"

#include "../Engine.hpp"

namespace Kedama
{
  StaticModel::StaticModel(RenderStreamPtr& rs):m_rs(rs)
  {
  }

  void StaticModel::SetRenderStream(RenderStreamPtr& rs)
  {
    m_rs=rs;
  }

  const RenderStreamPtr& StaticModel::GetRenderStream()
  {
    return m_rs;
  }

  void DynamicModel::SetRenderStream(RenderStreamPtr& rs)
  {
    m_rs=rs;
  }


  const RenderStreamPtr& DynamicModel::GetRenderStream()
  {
    return m_rs;
  }

}
