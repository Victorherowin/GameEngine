#ifndef CAMERA
#define CAMERA

#include "GameObject.hpp"
#include "../Include.hpp"
#include "../Define.hpp"

namespace Kedama{

  class Camera:public GameObject
  {
  private:
    enum class LookType
    {
      Target,Position,Direction
    };

    public:
    explicit Camera(const string& name);
    glm::mat4 GetViewMatrix();

    void SetPerspective(float fov,float aspect,float near,float far);

    inline const glm::mat4& GetProjectionMatrix()
    {return m_projection_matrix;}

    inline float GetFOV(){return m_fov;}
    inline float GetAspect(){return m_aspect;}
    inline float GetNear(){return m_near;}
    inline float GetFar(){return m_far;}

    void LookAt(GameObject* target);
    void LookAt(const glm::vec3& target);
    void LookDirection(const glm::vec3& direction);

  protected:
    LookType m_type;
    float m_fov,m_aspect,m_near,m_far;

    glm::vec3 m_target_position;
    glm::vec3 m_direction;
    GameObject* m_look_target=nullptr;

    glm::mat4 m_view_matrix;
    glm::mat4 m_projection_matrix;
  };
}

#endif
