#ifndef GAMEOBJECT
#define GAMEOBJECT

#include <vector>

#include "Transform.hpp"
#include "../Include.hpp"
#include "../Define.hpp"

namespace Kedama
{
  DEFINE_SHARED_PTR(GameObject)

  using namespace std;

  class KEDAMA_API GameObject : protected Transform,public std::enable_shared_from_this<GameObject>
  {
  public:

    GameObject(const string& name=string());
    virtual ~GameObject();
    Transform& GetTansform();

    inline const string& GetName()
    {return m_name;}

    inline GameObjectPtr GetParentNode()
    {return m_parent;}

    void AddNode(GameObjectPtr node);
    GameObjectPtr GetChildNode(const string& name);
    bool RemoveNode(GameObjectPtr node);

    static GameObjectPtr CreateGameObject(const string& name);
  private:
    void UpdateSelf();
    void UpdateChildren();

  private:
    string m_name;

    GameObjectPtr m_parent=nullptr;
    std::list<GameObjectPtr> m_children;
  };
}

#endif
