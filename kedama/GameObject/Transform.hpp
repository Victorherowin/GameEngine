#ifndef TRANSFORM
#define TRANSFORM

#include "../Include.hpp"

#include <list>

namespace Kedama
{
  using namespace std;

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

    void SetRelativeMatrix(const glm::mat4& mat);
    void SetWorldMatrix(const glm::mat4& mat);

    void SetScale(const glm::vec3& scale);

    inline const glm::vec3& GetRelativePosition(){return m_position;}
    inline const glm::quat& GetRelativeAngle(){return m_angle;}
    inline const glm::mat4& GetRelativeMatrix(){return m_relative_matrix;}
    inline const glm::vec3& GetScale(){return m_scale;}

    glm::quat GetWorldAngle();
    glm::vec3 GetWorldPosition();
    const glm::mat4& GetWorldMatrix();
    const glm::mat4& GetModelMatrix();

    void Move(const glm::vec3& distance);
    void Rotate(const glm::quat& angle);
    void Rotate(const glm::mat3& angle);
    void Rotate(const glm::vec3& axis,float rad);

    void AddUpdateListener(const function<void(Transform&)>& listener);
    void ClearListener();

    void Update();
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

    list<function<void(Transform&)>> m_listener_list;
  };
}

#endif
