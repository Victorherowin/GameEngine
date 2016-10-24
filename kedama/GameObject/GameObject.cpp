#include "GameObject.hpp"

namespace Kedama
{
  GameObjectPtr GameObject::CreateGameObject(const std::string &name)
  {
    static char _tmp_buf_[12];
    static uint32_t __undefined_counter__=0;
    string _name(name);

    if(name.empty())
    {
      sprintf(_tmp_buf_,"%u",__undefined_counter__++);
      _name=string("unnamed")+_tmp_buf_;
    }
    return std::make_shared<GameObject>(_name);
  }

  GameObject::GameObject(const std::string &name):m_name(name),Transform(this)
  {
  }

  GameObject::~GameObject()
  {
  }

  void GameObject::AddNode(GameObjectPtr node)
  {
    if(node==shared_from_this())throw std::runtime_error("Can't add self");
    node->m_parent=shared_from_this();
    m_children.push_back(node);
  }

  void GameObject::UpdateSelf()
  {
    m_relative_matrix=glm::mat4_cast(m_angle);
    m_relative_matrix[3]=glm::vec4(m_position,1.0f);

    if(m_parent!=nullptr)
      m_world_matrix=m_parent->m_world_matrix*m_relative_matrix;
    else
      m_world_matrix=m_relative_matrix;
    m_need_update=false;
  }

  void GameObject::UpdateChildren()
  {
    if(m_need_update)//更新子节点
    {
      UpdateSelf();
      for(GameObjectPtr node:m_children)
      {
        node->m_need_update=true;
        node->UpdateChildren();
      }
    }
  }

  void GameObject::Update()
  {
    UpdateChildren();
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
        cnode->m_relative_matrix=cnode->m_world_matrix;
        cnode->m_position=glm::vec3(cnode->m_relative_matrix[3]);
        cnode->m_angle=glm::quat_cast(glm::mat3(cnode->m_relative_matrix));
        return true;
      }
      cnode->RemoveNode(node);
    }
    return false;
  }


  Transform& GameObject::GetTansform()
  {
    return *this;
  }
}
