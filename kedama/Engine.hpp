#ifndef ENGINE
#define ENGINE

#include <string>

#include "utility/Singleton.hpp"

#include "SceneManager.hpp"
#include "AssetManager.hpp"
#include "RenderSystem/RendererFactoryManager.hpp"
#include "RenderSystem/RenderSystem.hpp"
#include "Log.hpp"

namespace Kedama
{
  using std::string;
  class Engine:public Singleton<Engine>
  {
  public:
    Engine(const string& render_system_name);
    ~Engine();

    RenderSystem* GetRenderSystem();
    AssetManager* GetAssetManager();
    SceneManager* GetSceneManager();
    IRendererFactory* GetRendererFactory();
    string GetRendererName();

  private:
    Log m_logger;
    RendererFactoryManager* m_renderer_factory_manager=nullptr;
    AssetManager* m_asset_manager=nullptr;
    SceneManager* m_scene_manager=nullptr;
    RenderSystem* m_render_system=nullptr;
    IRendererFactory* m_renderer_factory=nullptr;
  };
}

#endif
