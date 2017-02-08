#ifndef _H_RENDERERFACTORYMANAGER
#define _H_RENDERERFACTORYMANAGER

#include "../Include.hpp"
#include "../utility/Singleton.hpp"

#include "Interface/IRendererFactory.hpp"

namespace Kedama
{
  using std::map;

  class KEDAMA_API RendererFactoryManager:public Singleton<RendererFactoryManager>
  {
  public:
    RendererFactoryManager()=default;
    ~RendererFactoryManager();

    int32_t RegisterFactory(const string& name,IRendererFactory* irsf);
    int32_t UnregisterFactory(const string& name);
    IRendererFactory* GetFactory(const string& name);

  private:
    map<string,IRendererFactory*> m_render_system_factory_map;
  };
}

#endif
