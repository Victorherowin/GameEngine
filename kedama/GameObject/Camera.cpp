#include "Camera.hpp"

namespace Kedama
{
  Camera::Camera(const string& name):GameObject(name)
  {
  }

  void Camera::LookAt(const glm::vec3 &position)
  {
    m_look_target=nullptr;
    m_target_position=position;
  }

  void Camera::LookAt(GameObject* target)
  {
    m_look_target=target;
  }

  void Camera::LookDirect(const glm::vec3 &direction)
  {
    m_look_target=nullptr;
    m_target_position=glm::normalize(direction)+GetTansform()->GetWorldPosition();
  }

  const glm::mat4& Camera::GetViewMatrix()
  {
    if(m_look_target==nullptr)
    {
      m_view_matrix=glm::lookAt(GetTansform()->GetWorldPosition(),m_target_position,glm::vec3(0.0f,1.0f,0.0f));
    }
    else
    {
      m_view_matrix=glm::lookAt(GetTansform()->GetWorldPosition(),m_look_target->GetTansform()->GetWorldPosition(),glm::vec3(0.0f,1.0f,0.0f));
    }
    return m_view_matrix;
  }
}
