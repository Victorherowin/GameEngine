#include "Camera.hpp"

namespace Kedama
{
  Camera::Camera(const string& name):GameObject(name)
  {
  }

  void Camera::LookAt(const glm::vec3 &position)
  {
    m_type=LookType::Position;
    m_target_position=position;
  }

  void Camera::LookAt(GameObject* target)
  {
    m_type=LookType::Target;
    m_look_target=target;
  }

  void Camera::LookDirection(const glm::vec3 &direction)
  {
    m_type=LookType::Direction;
    m_direction=glm::normalize(direction);
  }

  glm::mat4 Camera::GetViewMatrix()
  {
    if(m_type==LookType::Position)
    {
      return glm::lookAt(GetWorldPosition(),m_target_position,glm::vec3(0.0f,1.0f,0.0f));
    }
    else if(m_type==LookType::Target)
    {
      return glm::lookAt(GetWorldPosition(),m_look_target->GetWorldPosition(),glm::vec3(0.0f,1.0f,0.0f));
    }
    else
    {
      return glm::lookAt(GetWorldPosition(),m_direction+GetWorldPosition(),glm::vec3(0.0f,1.0f,0.0f));
    }
  }

  void Camera::SetPerspective(float fov, float aspect, float near, float far)
  {
    m_fov=fov;
    m_aspect=aspect;
    m_near=near;
    m_far=far;
    m_projection_matrix=glm::perspective(fov,aspect,near,far);
  }
}
