#include "SceneManager.hpp"
#include "GameObject/GameObject.hpp"

namespace Kedama
{
  SceneManager::SceneManager(unique_ptr<RenderSystem>& render_system):
    m_render_system(render_system),
    m_object_root(new GameObject("__root__"))
  {
    m_render_system->Clear();
    m_render_system->SwapBuffer();
  }

  SceneManager::~SceneManager()
  {
    delete m_object_root;
  }

  GameObject* SceneManager::GetRoot()
  {
    return m_object_root;
  }

  void SceneManager::Update()
  {
    //TODO:其他的一些更新
    m_object_root->Update();
  }
}
