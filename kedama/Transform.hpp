#ifndef TRANSFORM
#define TRANSFORM

#include "Config.hpp"

#include <list>

namespace Kedama
{

  class GameObject;

  class Transform
  {
  public:
    explicit Transform(GameObject* obj);

    void SetRelativePosition(const glm::vec3& position);
    void SetWorldPosition(const glm::vec3& position);

    void SetRelativeAngle(const glm::quat& angle);
    void SetWorldAngle(const glm::quat& angle);//四元数
    void SetRelativeAngle(const glm::mat3& angle);
    void SetWorldAngle(const glm::mat3& angle);//矩阵

    void SetScale(const glm::vec3& scale);

    inline const glm::vec3& GetRelativePosition(){return m_position;}
    glm::vec3 GetWorldPosition();

    inline const glm::vec3& GetScale(){return m_scale;}

    inline const glm::quat& GetRelativeAngle(){return m_angle;}
    glm::quat GetWorldAngle();

    inline glm::mat4 GetRelativeMatrix(){return glm::scale(m_relative_matrix,m_scale);}
    inline glm::mat4 GetWorldMatrix(){return glm::scale(m_world_matrix,m_scale);}

    void Move(const glm::vec3& distance);
    void Rotate(const glm::quat& angle);
    void Rotate(const glm::mat3& angle);
    void Rotate(const glm::mat4 angle);
  private:
    void CheckUpdate();

  private:

    bool m_need_update=false;
    GameObject* m_object;

    //相对位置
    glm::vec3 m_position;
    glm::quat m_angle;
    glm::vec3 m_scale=glm::vec3(1.0f,1.0f,1.0f);

    //相对位置矩阵
    glm::mat4 m_relative_matrix;
    //绝对位置矩阵
    glm::mat4 m_world_matrix;

    friend class GameObject;
  };
}

#endif
