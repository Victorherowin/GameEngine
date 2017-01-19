#include "GameObject.hpp"

namespace Kedama
{

  GameObject::GameObject(const std::string &name):m_name(name),m_transform(this)
  {
  }

  GameObject::~GameObject()
  {
  }

  void GameObject::AddNode(GameObject* node)
  {
    if(node==this)throw std::runtime_error("Can't add self");
    node->m_parent=this;
    m_children.push_back(node);
  }

  GameObject* GameObject::GetChild(const std::string &name)
  {
    for(GameObject* node:m_children)
    {
      if(node->GetName()==name)
        return node;
      return node->GetChild(name);
    }
    return nullptr;
  }

  bool GameObject::RemoveNode(GameObject* node)
  {
    for(GameObject* cnode:m_children)
    {
      if(cnode==node)
      {
        Transform *ct=cnode->GetTansform();
        cnode->m_parent=nullptr;
        ct->SetRelativeMatrix(ct->GetWorldMatrix());
        ct->SetRelativePosition(glm::vec3(ct->GetRelativeMatrix()[3]));
        ct->SetRelativeAngle(glm::quat_cast(glm::mat3(ct->GetRelativeMatrix())));
        return true;
      }
      cnode->RemoveNode(node);
    }
    return false;
  }


  Transform* GameObject::GetTansform()
  {
    return &m_transform;
  }
}
