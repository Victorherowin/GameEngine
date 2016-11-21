#include "Transform.hpp"
#include "GameObject.hpp"

namespace Kedama {

  Transform::Transform(GameObject* obj):m_object(obj),m_scale(glm::vec3(1.0f,1.0f,1.0f))
  {
  }

  void Transform::AddUpdateListener(const function<void (Transform &)> &listener)
  {
    m_listener_list.push_back(listener);
  }

  void Transform::ClearListener()
  {
    m_listener_list.clear();
  }

  void Transform::SetRelativePosition(const glm::vec3& position)
  {
    m_position=position;
    m_need_update=true;
  }

  void Transform::SetWorldPosition(const glm::vec3& position)
  {
    const Transform* parent=reinterpret_cast<Transform*>(m_object->GetParentNode().get());
    m_position=glm::vec3(glm::inverse(parent->m_world_matrix)*glm::vec4(position,1.0f));
    m_need_update=true;
  }

  void Transform::SetRelativeAngle(const glm::quat& angle)
  {
    m_angle=angle;
    m_need_update=true;
  }

  void Transform::SetRelativeAngle(const glm::mat3& angle)
  {
    m_angle=glm::quat_cast(angle);
    m_need_update=true;
  }

  void Transform::SetWorldAngle(const glm::mat3& angle)
  {
    const Transform* parent=reinterpret_cast<Transform*>(m_object->GetParentNode().get());
    m_angle=glm::quat_cast(glm::transpose(glm::mat3(parent->m_world_matrix)*angle));
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
    m_angle=glm::quat_cast(glm::mat3_cast(m_angle)*angle);
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
      for(auto& func:m_listener_list)
        func(*this);
    }
    return glm::vec3(m_world_matrix[3]);
  }

  glm::quat Transform::GetWorldAngle()
  {
    if(m_need_update)
    {
      for(auto& func:m_listener_list)
        func(*this);
    }
    return glm::quat_cast(glm::mat3(m_world_matrix));
  }

  const glm::mat4& Transform::GetWorldMatrix()
  {
    if(m_need_update)
    {
      for(auto& func:m_listener_list)
        func(*this);
    }
    return m_world_matrix;
  }

  const glm::mat4& Transform::GetModelMatrix()
  {
    if(m_need_update)
    {
      for(auto& func:m_listener_list)
        func(*this);
    }
    m_model_matirx=glm::scale(m_world_matrix,m_scale);
    return m_model_matirx;
  }

}
