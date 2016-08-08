#include "Mesh.hpp"

#include "../Engine.hpp"

namespace Kedama
{
  StaticModel::StaticModel(const string& name):GameObject(name)
  {
    m_rs=Engine::GetSingleton().GetRenderSystemFactory()->CreateRenderStream();
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
