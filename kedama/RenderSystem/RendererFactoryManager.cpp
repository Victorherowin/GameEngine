#include "RendererFactoryManager.hpp"

namespace Kedama
{
  int32_t RendererFactoryManager::RegisterFactory(const string& name,IRendererFactory* irsf)
  {
    auto it=m_render_system_factory_map.find(name);
    if(it==m_render_system_factory_map.end())
    {
      m_render_system_factory_map[name]=irsf;
      return 0;
    }
    return -1;
  }

  int32_t RendererFactoryManager::UnregisterFactory(const string& name)
  {
    auto it=m_render_system_factory_map.find(name);
    if(it==m_render_system_factory_map.end())
      return -1;
    m_render_system_factory_map.erase(it);
    return 0;
  }

  IRendererFactory* RendererFactoryManager::GetFactory(const string& name)
  {
    auto it=m_render_system_factory_map.find(name);
    if(it==m_render_system_factory_map.end())
      return nullptr;
    return it->second;
  }

  RendererFactoryManager::~RendererFactoryManager()
  {
    for(auto& it:m_render_system_factory_map)
    {
      delete it.second;
    }
  }
};
