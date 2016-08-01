#include "SceneManager.hpp"

namespace Kedama
{
  SceneManager::SceneManager(IRenderSystem* render_system):
    m_render_system(render_system),
    m_object_root("__root__")
  {
    m_render_system->Clear();
    m_render_system->SwapBuffer();
  }

  GameObject& SceneManager::GetRoot()
  {
    return m_object_root;
  }
}
