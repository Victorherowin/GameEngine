#include "RenderSystemFactoryManager.hpp"

static Kedama::RenderSystemFactoryManager render_system_factory_manager;

namespace Kedama
{
  int32_t RenderSystemFactoryManager::RegisterFactory(const string& name,IRenderSystemFactory* irsf)
  {
    auto it=m_render_system_factory_map.find(name);
    if(it==m_render_system_factory_map.end())
      {
        m_render_system_factory_map[name]=irsf;
        return 0;
      }
    return -1;
  }

  int32_t RenderSystemFactoryManager::UnregisterFactory(const string& name)
  {
    auto it=m_render_system_factory_map.find(name);
    if(it==m_render_system_factory_map.end())
      return -1;
    m_render_system_factory_map.erase(it);
    return 0;
  }

  IRenderSystemFactory* RenderSystemFactoryManager::GetFactory(const string& name)
  {
    auto it=m_render_system_factory_map.find(name);
    if(it==m_render_system_factory_map.end())
      return nullptr;
    return it->second;
  }

  RenderSystemFactoryManager::~RenderSystemFactoryManager()
  {
    for(auto& it:m_render_system_factory_map)
      {
        delete it.second;
      }
  }

};
