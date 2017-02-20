#include "Transform.hpp"
#include "GameObject.hpp"

namespace Kedama {

  Transform::Transform(GameObject* obj):m_object(obj),m_scale(glm::vec3(1.0f,1.0f,1.0f))
  {
  }

  void Transform::SetRelativeMatrix(const glm::mat4 &mat)
  {
    m_relative_matrix=mat;
    m_need_update=true;
  }

  void Transform::SetWorldMatrix(const glm::mat4 &mat)
  {
    m_world_matrix=mat;
    m_need_update=true;
  }

  void Transform::SetRelativePosition(const glm::vec3& position)
  {
    m_position=position;
    m_need_update=true;
  }

  void Transform::SetWorldPosition(const glm::vec3& position)
  {
    if(m_object->GetParent()!=nullptr)
    {
      const Transform* parent=m_object->GetParent()->GetTansform();
      m_position=glm::vec3(glm::inverse(parent->m_world_matrix)*glm::vec4(position,1.0f));
      m_need_update=true;
    }
    else
      SetRelativePosition(position);

  }

  void Transform::SetRelativeAngle(const glm::quat& angle)
  {
    m_angle=glm::mat3_cast(angle);
    m_need_update=true;
  }

  void Transform::SetRelativeAngle(const glm::mat3& angle)
  {
    m_angle=angle;
    m_need_update=true;
  }

  void Transform::SetWorldAngle(const glm::mat3& angle)
  {
    const Transform* parent=m_object->GetParent()->GetTansform();
    m_angle=glm::transpose(glm::mat3(parent->m_world_matrix)*angle);
    m_need_update=true;
  }

  void Transform::SetWorldAngle(const glm::quat& angle)
  {
    SetWorldAngle(glm::mat3_cast(angle));
  }

  void Transform::SetScale(const glm::vec3 &scale)
  {
    m_scale=scale;//缩放不对子节点生效
  }

  void Transform::Move(const glm::vec3& distance)
  {
    m_position+=distance;
    m_need_update=true;
  }

  void Transform::Rotate(const glm::mat3& angle)
  {
    m_angle=angle*m_angle;
    m_need_update=true;
  }

  void Transform::Rotate(const glm::vec3 &axis, float rad)
  {
    Rotate(glm::mat3(glm::rotate(rad,axis)));
  }

  void Transform::Rotate(const glm::quat& angle)
  {
    Rotate(glm::mat3_cast(angle));
  }

  glm::vec3 Transform::GetWorldPosition()
  {
    if(m_need_update)
    {
      UpdateSelf();
      SetChildrenNeedUpdateFlag();
    }
    return glm::vec3(m_world_matrix[3]);
  }

  glm::quat Transform::GetWorldAngle()
  {
    if(m_need_update)
    {
      UpdateSelf();
      SetChildrenNeedUpdateFlag();
    }
    return glm::quat_cast(glm::mat3(m_world_matrix));
  }

  const glm::mat4& Transform::GetWorldMatrix()
  {
    if(m_need_update)
    {
      UpdateSelf();
      SetChildrenNeedUpdateFlag();
    }
    return m_world_matrix;
  }

  const glm::mat4& Transform::GetModelMatrix()
  {
    if(m_need_update)
    {
      UpdateSelf();
      SetChildrenNeedUpdateFlag();
    }
    m_model_matirx=glm::scale(m_world_matrix,m_scale);
    return m_model_matirx;
  }

  void Transform::SetChildrenNeedUpdateFlag()
  {
    for(GameObject* node:m_object->GetChildren())
    {
      if(!node->GetTansform()->m_need_update)
      {
        node->GetTansform()->m_need_update=true;
      }
      if(node->GetTansform()->m_need_update)
      {
        node->GetTansform()->SetChildrenNeedUpdateFlag();
      }
    }
  }

  void Transform::UpdateChildren()
  {
    for(GameObject* node:m_object->GetChildren())
    {
      node->GetTansform()->UpdateSelf();
      node->GetTansform()->UpdateChildren();
    }
  }

  void Transform::UpdateSelf()
  {
    if(m_need_update)
    {
      //更新自己
      m_relative_matrix=glm::mat4(m_angle);
      m_relative_matrix[3]=glm::vec4(m_position,1.0f);

      if(m_object->GetParent()!=nullptr)
        m_world_matrix=m_object->GetParent()->GetTansform()->m_world_matrix*m_relative_matrix;
      else
        m_world_matrix=m_relative_matrix;
      m_need_update=false;
    }
  }

  void Transform::Update()
  {
    UpdateSelf();
    SetChildrenNeedUpdateFlag();
    UpdateChildren();
  }

}
