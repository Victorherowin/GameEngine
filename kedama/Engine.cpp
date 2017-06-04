#include "Include.hpp"
#include "Engine.hpp"

namespace Kedama
{
  Engine::Engine(const string& api_name)
  {
    m_renderer_factory=RendererFactoryManager::GetSingletonPtr()->GetFactory(api_name);
    m_render_system=new RenderSystem(m_renderer_factory);
    m_asset_manager=new AssetManager();
    m_scene_manager=new SceneManager(m_render_system);
  }

  Engine::~Engine()
  {
    delete m_scene_manager;
    delete m_render_system;
    delete m_asset_manager;
  }

  RenderSystem* Engine::GetRenderSystem()
  {
    return m_render_system;
  }

  AssetManager* Engine::GetAssetManager()
  {
    return m_asset_manager;
  }

  SceneManager* Engine::GetSceneManager()
  {
    return m_scene_manager;
  }

  IRendererFactory* Engine::GetRendererFactory()
  {
    return m_renderer_factory;
  }
}
