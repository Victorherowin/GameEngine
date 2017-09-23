#include "Transform.hpp"
#include "GameObject.hpp"

namespace Kedama {

  Transform::Transform():m_scale(vec3(1.0f,1.0f,1.0f))
  {
  }

  void Transform::SetRelativeMatrix(const mat4 &mat)
  {
    m_relative_matrix=mat;
    m_need_update=true;
  }

  void Transform::SetWorldMatrix(const mat4 &mat)
  {
    m_world_matrix=mat;
    m_need_update=true;
  }

  void Transform::SetRelativePosition(const vec3& position)
  {
    m_position=position;
    m_need_update=true;
  }

  void Transform::SetWorldPosition(const vec3& position)
  {
    if(m_parent!=nullptr)
    {
      m_position=vec3(inverse(m_parent->m_world_matrix)*vec4(position,1.0f));
      m_need_update=true;
    }
    else
      SetRelativePosition(position);
  }

  void Transform::SetRelativeAngle(const quat& angle)
  {
    m_angle=angle;
    m_need_update=true;
  }

  void Transform::SetRelativeAngle(const mat3& angle)
  {
    m_angle=quat_cast(angle);
    m_need_update=true;
  }

  void Transform::SetWorldAngle(const mat3& angle)
  {
    SetWorldAngle(quat_cast(angle));
  }

  void Transform::SetWorldAngle(const quat& angle)
  {
    m_angle=quat(m_parent->m_inverse_world_matrix)*angle;
    m_need_update=true;
  }

  void Transform::SetScale(float sx,float sy,float sz)
  {
    m_scale=vec3(sx,sy,sz);//缩放不对子节点生效
  }

  void Transform::Move(const vec3& distance,SpaceType type)
  {
    if(type==SpaceType::Model)
    {
      m_position+=distance;
    }
    else
    {
      m_position=vec3(m_inverse_world_matrix*(m_world_matrix[3]+vec4(distance,0.0f)));
    }
    m_need_update=true;
  }

  void Transform::Rotate(const vec3 &axis, float rad,SpaceType type)
  {
    vec3 naxis=normalize(axis);
    float sino=glm::sin(rad*0.5f);
    float coso=glm::cos(rad*0.5f);
    Rotate(quat(coso,naxis*sino),type);
  }

  void Transform::Rotate(const quat& angle,SpaceType type)
  {
    if(type==SpaceType::Model)
    {
      m_angle=angle*m_angle;
    }
    else
    {
      m_angle=(quat(m_parent->m_inverse_world_matrix)*angle)*m_angle;
    }
    m_need_update=true;
  }

  vec3 Transform::GetWorldPosition()
  {
    if(m_need_update)
    {
      UpdateSelf();
      SetChildrenNeedUpdateFlag();
    }
    return vec3(m_world_matrix[3]);
  }

  quat Transform::GetWorldAngle()
  {
    if(m_need_update)
    {
      UpdateSelf();
      SetChildrenNeedUpdateFlag();
    }
    return quat_cast(mat3(m_world_matrix));
  }

  const mat4& Transform::GetWorldMatrix()
  {
    if(m_need_update)
    {
      UpdateSelf();
      SetChildrenNeedUpdateFlag();
    }
    return m_world_matrix;
  }

  const mat4& Transform::GetModelMatrix()
  {
    if(m_need_update)
    {
      UpdateSelf();
      SetChildrenNeedUpdateFlag();
    }
    m_model_matirx=scale(m_world_matrix,m_scale);
    return m_model_matirx;
  }

  void Transform::SetChildrenNeedUpdateFlag()
  {
    for(Transform* node:m_children)
    {
      if(!node->m_need_update)
      {
        node->m_need_update=true;
      }
      if(node->m_need_update)
      {
        node->SetChildrenNeedUpdateFlag();
      }
    }
  }

  void Transform::UpdateChildren()
  {
    for(Transform* node:m_children)
    {
      node->UpdateSelf();
      node->UpdateChildren();
    }
  }

  void Transform::UpdateSelf()
  {
    if(m_need_update)
    {
      //更新自己
      m_relative_matrix=mat4_cast(m_angle);
      m_relative_matrix[3]=vec4(m_position,1.0f);

      if(m_parent!=nullptr)
        m_world_matrix=m_parent->m_world_matrix*m_relative_matrix;
      else
        m_world_matrix=m_relative_matrix;
      m_inverse_world_matrix=glm::inverse(m_world_matrix);
      m_need_update=false;
      for (auto& p : m_listeners)
      {
        p.second(*this);
      }
    }
  }

  void Transform::Update()
  {
    UpdateSelf();
    SetChildrenNeedUpdateFlag();
    UpdateChildren();
  }

  void Transform::AddUpdateListener(const string& name, const UpdateListener& listener)
  {
    m_listeners[name] = listener;
  }

  void Transform::RemoveUpdateListener(const string& name)
  {
    auto it = m_listeners.find(name);
    if (it == m_listeners.end())
      throw Exception::RuntimeException("No Found Listener!");
    m_listeners.erase(it);
  }

  void Transform::AddChildren(Transform *c)
  {
    if(c==this)throw Exception::RuntimeException("Can't add self");
    c->m_parent=this;
    m_children.push_back(c);
  }

  bool Transform::RemoveNode(Transform* node,bool disconnect)
  {
    for(Transform* cnode:m_children)
    {
      if(cnode==node)
      {
        cnode->m_parent=nullptr;
        cnode->SetRelativeMatrix(cnode->GetWorldMatrix());
        cnode->SetRelativePosition(glm::vec3(cnode->GetRelativeMatrix()[3]));
        cnode->SetRelativeAngle(glm::quat_cast(glm::mat3(cnode->GetRelativeMatrix())));
        if(disconnect==true)
        {
          for(Transform* t:cnode->m_children)
          {
            m_children.push_back(t);
          }
          cnode->m_children.clear();
        }
        return true;
      }

    }
    return false;
  }

}
