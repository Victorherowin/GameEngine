#ifndef TRANSFORM
#define TRANSFORM

#include "../Include.hpp"

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

    inline const glm::mat4& GetRelativeMatrix(){return m_relative_matrix;}
    const glm::mat4& GetWorldMatrix();

    inline glm::mat4& GetModelMatrix()
    {
      m_model_matirx=glm::scale(m_world_matrix,m_scale);
      return m_model_matirx;
    }

    void Move(const glm::vec3& distance);
    void Rotate(const glm::quat& angle);
    void Rotate(const glm::mat3& angle);
    void Rotate(const glm::vec3& axis,float rad);

  protected:
    bool m_need_update=false;

    //相对位置
    glm::vec3 m_position;
    glm::quat m_angle;
    glm::vec3 m_scale;

    glm::mat4 m_relative_matrix;//相对位置矩阵
    glm::mat4 m_world_matrix;//绝对位置矩阵
    glm::mat4 m_model_matirx;//模型矩阵

    GameObject* m_object;
  };
}

#endif
