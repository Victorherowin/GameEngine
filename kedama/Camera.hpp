#ifndef CAMERA
#define CAMERA

#include "GameObject.hpp"
#include "Config.hpp"

namespace Kedama{
  DEFINE_SHARED_PTR(Camera)

  class Camera:public GameObject
  {
    public:
    explicit Camera(const string& name="camera");
    glm::mat4 GetVPMatrix();

    void LookAt(GameObject* target);
    void LookAt(const glm::vec3& target);
    void LookDirect(const glm::vec3& direction);

    void SetPerspective(float fov,float aspect,float near,float far);
    void SetOrtho(float left,float right,float buttom,float top);
  protected:
    glm::vec3 m_target_position;
    GameObject* m_look_target=nullptr;


    glm::mat4 m_projection_matrix;
    glm::mat4 m_view_matrix;
  };
}

#endif
