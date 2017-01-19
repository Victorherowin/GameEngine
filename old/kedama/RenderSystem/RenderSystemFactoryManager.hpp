#ifndef RENDERSYSTEMFACTORYMANAGER
#define RENDERSYSTEMFACTORYMANAGER

#include <map>
#include "../utility/Singleton.hpp"

#include "IRenderSystemFactory.hpp"

namespace Kedama
{
  using std::map;

  class KEDAMA_API RenderSystemFactoryManager:public Singleton<RenderSystemFactoryManager>
  {
  public:
    RenderSystemFactoryManager()=default;
    ~RenderSystemFactoryManager();

    int32_t RegisterFactory(const string& name,IRenderSystemFactory* irsf);
    int32_t UnregisterFactory(const string& name);
    IRenderSystemFactory* GetFactory(const string& name);

  private:
    map<string,IRenderSystemFactory*> m_render_system_factory_map;
  };
}

#endif
