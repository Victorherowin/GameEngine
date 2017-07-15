#ifndef SCENEMANAGER
#define SCENEMANAGER

#include "RenderSystem/RenderSystem.hpp"
#include "utility/Singleton.hpp"
#include <memory>

using namespace std;

namespace Kedama
{
  class KEDAMA_API SceneManager:public Singleton<SceneManager>
  {
  public:
    SceneManager(unique_ptr<RenderSystem>& irfs);
    ~SceneManager();
    GameObject* GetRoot();
    void Update();
  private:
    unique_ptr<RenderSystem>& m_render_system;
    GameObject* m_object_root;//场景管理树根
  };
}

#endif
