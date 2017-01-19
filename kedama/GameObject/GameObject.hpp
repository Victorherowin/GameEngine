#ifndef GAMEOBJECT
#define GAMEOBJECT

#include <vector>

#include "Transform.hpp"
#include "../Include.hpp"
#include "../Define.hpp"

namespace Kedama
{
  using namespace std;

  class KEDAMA_API GameObject
  {
  public:

    GameObject(const string& name=string());
    virtual ~GameObject();
    Transform* GetTansform();

    inline const string& GetName()
    {return m_name;}

    void AddNode(GameObject* node);
    bool RemoveNode(GameObject* node);

    GameObject* GetChild(const string& name);
    std::list<GameObject*>& GetChildren()
    {return m_children;}

    inline GameObject* GetParent()
    {return m_parent;}

  private:
    string m_name;
    Transform m_transform;

    GameObject* m_parent=nullptr;
    std::list<GameObject*> m_children;
  };
}

#endif
