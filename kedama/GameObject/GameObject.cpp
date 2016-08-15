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

  void GameObject::AddNode(GameObjectPtr node)
  {
    if(node==this)throw std::runtime_error("Can't add self");
    node->m_parent=this;
    m_children.push_back(node);
  }

  void GameObject::UpdateSelf()
  {
    m_transform.m_relative_matrix=glm::mat4_cast(m_transform.m_angle);
    m_transform.m_relative_matrix[3]=glm::vec4(m_transform.m_position,1.0f);

    /*for(GameObjectPtr it=m_parent;it!=nullptr;it=it->m_parent)
    {
      m_transform.m_world_matrix=it->m_transform.m_relative_matrix*m_transform.m_world_matrix;
    }*/
    if(m_parent!=nullptr)
      m_transform.m_world_matrix=m_parent->m_transform.m_world_matrix*m_transform.m_relative_matrix;
    else
      m_transform.m_world_matrix=m_transform.m_relative_matrix;

    m_transform.m_need_update=false;
  }

  void GameObject::UpdateChildren()
  {
    if(m_transform.m_need_update)//更新子节点
    {
      UpdateSelf();
      for(GameObjectPtr node:m_children)
      {
        node->m_transform.m_need_update=true;
        node->UpdateChildren();
      }
    }
  }

  GameObjectPtr GameObject::GetChildNode(const std::string &name)
  {
    for(GameObjectPtr node:m_children)
    {
      if(node->GetName()==name)
        return node;
      return node->GetChildNode(name);
    }
    return nullptr;
  }

  bool GameObject::RemoveNode(GameObjectPtr node)
  {
    for(GameObjectPtr cnode:m_children)
    {
      if(cnode==node)
      {
        cnode->m_parent=nullptr;
        cnode->m_transform.m_relative_matrix=cnode->m_transform.m_world_matrix;
        cnode->m_transform.m_position=glm::vec3(cnode->m_transform.m_relative_matrix[3]);
        cnode->m_transform.m_angle=glm::quat_cast(glm::mat3(cnode->m_transform.m_relative_matrix));
        return true;
      }
      cnode->RemoveNode(node);
    }
    return false;
  }

  Transform& GameObject::GetTansform()
  {
    return m_transform;
  }
}
