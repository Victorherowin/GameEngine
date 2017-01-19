#include "SceneManager.hpp"

namespace Kedama
{
  SceneManager::SceneManager(RenderSystem* render_system):
    m_render_system(render_system),
    m_object_root(GameObject("__root__"))
  {
    m_render_system->Clear();
    m_render_system->SwapBuffer();
  }

  GameObject& SceneManager::GetRoot()
  {
    return m_object_root;
  }

  void SceneManager::Update()
  {
    //TODO:其他的一些更新
    m_object_root.GetTansform()->Update();
  }
}
