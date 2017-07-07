#include "GameObject.hpp"

namespace Kedama
{

  GameObject::GameObject(const std::string &name):m_name(name)
  {
  }

  GameObject::~GameObject()
  {
  }

  GameObject* GameObject::GetChild(const string &name)
  {
    for(Transform* p:GetChildren())
    {
      GameObject* gp=static_cast<GameObject*>(p);
      if(gp->GetName()==name)
        return gp;
    }
    return nullptr;
  }
}
