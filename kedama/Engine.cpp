#include "Include.hpp"
#include "Engine.hpp"

namespace Kedama
{
    Engine::Engine(const string& api_name)
    {
        m_renderer_factory = RendererFactoryManager::GetSingletonPtr()->GetFactory(api_name);
        m_render_system = unique_ptr<RenderSystem>(new RenderSystem(m_renderer_factory));
        m_asset_manager = unique_ptr<AssetManager>(new AssetManager());
        m_scene_manager = unique_ptr<SceneManager>(new SceneManager(m_render_system));
        m_physics_system = unique_ptr<Physics::PhysicsSystem>(new Physics::PhysicsSystem());
        m_root_file_system = unique_ptr<FileSystem::FileSystemContext>(new FileSystem::FileSystemContext());
    }

    Engine::~Engine()
    {
    }

    unique_ptr<RenderSystem>& Engine::GetRenderSystem()
    {
        return m_render_system;
    }

    unique_ptr<AssetManager>& Engine::GetAssetManager()
    {
        return m_asset_manager;
    }

    unique_ptr<SceneManager>& Engine::GetSceneManager()
    {
        return m_scene_manager;
    }

    IRendererFactory* Engine::GetRendererFactory()
    {
        return m_renderer_factory;
    }

    unique_ptr<FileSystem::FileSystemContext>& Engine::GetFileSystem()
    {
        return m_root_file_system;
    }

    unique_ptr<Physics::PhysicsSystem>& Engine::GetPhysicsSystem()
    {
        return m_physics_system;
    }
}
