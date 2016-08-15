#ifndef CAMERA
#define CAMERA

#include "GameObject.hpp"
#include "../Config.hpp"

namespace Kedama{
  DEFINE_RAW_PTR(Camera)

  class Camera:public GameObject
  {
    public:
    explicit Camera(const string& name="camera");
    const glm::mat4& GetViewMatrix();
    const glm::mat4& GetProjectionMatrix();

    void LookAt(GameObjectPtr target);
    void LookAt(const glm::vec3& target);
    void LookDirect(const glm::vec3& direction);

    void SetPerspective(float fov,float aspect,float near,float far);
    void SetOrtho(float left,float right,float buttom,float top);


    static CameraPtr CreateCamera(const string& name);
  protected:
    glm::vec3 m_target_position;
    GameObjectPtr m_look_target=nullptr;


    glm::mat4 m_projection_matrix;
    glm::mat4 m_view_matrix;
  };
}

#endif
