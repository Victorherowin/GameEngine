#ifndef ENGINE
#define ENGINE

#include <string>

#include "utility/Singleton.hpp"

#include "SceneManager.hpp"
#include "AssetManager.hpp"
#include "RenderSystem/RenderSystemFactoryManager.hpp"
#include "RenderSystem/IRenderSystem.hpp"
#include "Log.hpp"

namespace Kedama
{
  using std::string;
  class Engine:public Singleton<Engine>
  {
  public:
    Engine(const string& render_system_name);
    ~Engine();

    IRenderSystem* GetRenderSystem();
    AssetManager* GetAssetManager();
    SceneManager* GetSceneManager();
    IRenderSystemFactory* GetRenderRenderFactory();
    string GetRenderSystemName();

  private:

    AssetManager* m_asset_manager=nullptr;
    SceneManager* m_scene_manager=nullptr;
    string m_render_system_name=nullptr;
    IRenderSystem* m_render_system=nullptr;
  };
}

#endif
