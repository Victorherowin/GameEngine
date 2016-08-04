#include "GameObject.hpp"

namespace Kedama
{
  GameObject::GameObject(const std::string &name):m_name(name),m_transform(this)
  {

  }

  GameObject::~GameObject()
  {
    for(GameObjectPtr ptr:m_children)
    {
      delete ptr;
    }
  }

  void GameObject::AddNode(GameObject *node)
  {
    node->m_parent=this;
    m_children.push_back(node);
  }

  void GameObject::UpdateSelf()
  {
    m_transform.SetRelativeAngle(m_transform.m_angle);
    m_transform.SetRelativePosition(m_transform.m_position);
    m_transform.m_world_matrix=m_transform.m_relative_matrix;
    for(GameObject* it=m_parent;it!=nullptr;it=it->m_parent)
    {
        m_transform.m_world_matrix=it->m_transform.m_relative_matrix*m_transform.m_world_matrix;
    }
  }

  void GameObject::UpdateChildren()
  {
    if(m_transform.m_need_update)//更新子节点
    {
        for(GameObject* node:m_children)
        {
           node->m_transform.m_need_update=true;
           node->UpdateChildren();
        }
        UpdateSelf();
        m_transform.m_need_update=false;
    }
  }
}
