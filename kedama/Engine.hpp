#ifndef ENGINE
#define ENGINE

#include <string>

#include "utility/Singleton.hpp"

#include "SceneManager.hpp"
#include "AssetManager.hpp"
#include "RenderSystem/RendererFactoryManager.hpp"
#include "RenderSystem/RenderSystem.hpp"
#include "PhysicsSystem/PhysicsSystem.hpp"
#include "Log.hpp"

namespace Kedama
{
    using std::string;

    class KEDAMA_API Engine : public Singleton<Engine>
    {
    public:
        Engine(const string& render_system_name);

        ~Engine();

        unique_ptr<RenderSystem>& GetRenderSystem();

        unique_ptr<AssetManager>& GetAssetManager();

        unique_ptr<SceneManager>& GetSceneManager();
        unique_ptr<Physics::PhysicsSystem>& GetPhysicsSystem();

        IRendererFactory* GetRendererFactory();

        string GetRendererName();

    private:
        Logger m_logger;
        unique_ptr<AssetManager> m_asset_manager = nullptr;
        unique_ptr<SceneManager> m_scene_manager = nullptr;
        unique_ptr<RenderSystem> m_render_system = nullptr;
        unique_ptr<Physics::PhysicsSystem> m_physics_system = nullptr;
        IRendererFactory* m_renderer_factory = nullptr;
    };
}

#endif
