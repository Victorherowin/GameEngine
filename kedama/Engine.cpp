#include "Config.hpp"

#include "Engine.hpp"

namespace Kedama
{
  Engine::Engine(const string& render_system_name):
    m_render_system(RenderSystemFactoryManager::GetSingleton().GetFactory(render_system_name)->CreateRenderSystem()),
    m_render_system_name(render_system_name)
  {
    m_asset_manager=new AssetManager();
    m_scene_manager=new SceneManager(m_render_system);
  }

  Engine::~Engine()
  {
    delete m_scene_manager;

    RenderSystemFactoryManager::GetSingleton().GetFactory(m_render_system_name)->DeleteRenderSystem(m_render_system);
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

  IRenderSystemFactory* Engine::GetRenderRenderFactory()
  {
    return RenderSystemFactoryManager::GetSingleton().GetFactory(m_render_system_name);
  }

  string Engine::GetRenderSystemName()
  {
    return m_render_system_name;
  }
}
