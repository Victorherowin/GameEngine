#ifndef TRANSFORM
#define TRANSFORM

#include "../Define.hpp"
#include "../Include.hpp"
#include "../GLMInclude.hpp"

#include <list>

namespace Kedama
{
  using namespace std;
  using namespace glm;

  class GameObject;

  class KEDAMA_API Transform
  {
  public:
    explicit Transform(GameObject* obj);

    void SetRelativePosition(const vec3& position);
    void SetWorldPosition(const vec3& position);

    void SetRelativeAngle(const quat& angle);
    void SetWorldAngle(const quat& angle);//四元数
	void SetRelativeAngle(const mat3& angle);
    void SetWorldAngle(const mat3& angle);//矩阵

    void SetRelativeMatrix(const mat4& mat);
    void SetWorldMatrix(const mat4& mat);

    void SetScale(const vec3& scale);

    inline const vec3& GetRelativePosition(){return m_position;}
    inline const quat GetRelativeAngle(){return quat_cast(m_angle);}
    inline const mat4& GetRelativeMatrix(){return m_relative_matrix;}
    inline const vec3& GetScale(){return m_scale;}

    quat GetWorldAngle();
    vec3 GetWorldPosition();
    const mat4& GetWorldMatrix();
    const mat4& GetModelMatrix();

    void Move(const vec3& distance);
    void Rotate(const quat& angle);
    void Rotate(const mat3& angle);
    void Rotate(const vec3& axis,float rad);

    void Update();

  private:
    void SetChildrenNeedUpdateFlag();
    void UpdateSelf();
    void UpdateChildren();

  protected:
    bool m_need_update=false;

    //相对位置
    vec3 m_position;
    mat3 m_angle;
    vec3 m_scale;

    mat4 m_relative_matrix;//相对位置矩阵
    mat4 m_world_matrix;//绝对位置矩阵
    mat4 m_model_matirx;//模型矩阵

    GameObject* m_object;
  };
}

#endif
