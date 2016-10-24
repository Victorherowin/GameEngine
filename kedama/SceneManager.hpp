#ifndef SCENEMANAGER
#define SCENEMANAGER

#include "RenderSystem/RenderSystem.hpp"
#include "utility/Singleton.hpp"
#include <memory>

using namespace std;

namespace Kedama
{
  class SceneManager:public Singleton<SceneManager>
  {
  public:
    SceneManager(RenderSystem* irfs);
    GameObject& GetRoot();

  private:
    RenderSystem* m_render_system;
    GameObjectPtr m_object_root;
  };
}

#endif
