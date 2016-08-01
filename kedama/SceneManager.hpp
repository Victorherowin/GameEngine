#ifndef SCENEMANAGER
#define SCENEMANAGER

#include "RenderSystem/IRenderSystem.hpp"
#include "utility/Singleton.hpp"
#include <memory>

using namespace std;

namespace Kedama
{
  class SceneManager:public Singleton<SceneManager>
  {
  public:
    SceneManager(IRenderSystem* irfs);
    GameObject& GetRoot();

  private:
    IRenderSystem* m_render_system;
    GameObject m_object_root;
  };
}

#endif
