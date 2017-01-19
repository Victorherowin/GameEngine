#ifndef CAMERA
#define CAMERA

#include "GameObject.hpp"
#include "../Include.hpp"
#include "../Define.hpp"

namespace Kedama{

  class Camera:public GameObject
  {
    public:
    explicit Camera(const string& name="camera");
    const glm::mat4& GetViewMatrix();

    void LookAt(GameObject* target);
    void LookAt(const glm::vec3& target);
    void LookDirect(const glm::vec3& direction);

    static Camera* CreateCamera(const string& name);
  protected:
    glm::vec3 m_target_position;
    GameObject* m_look_target=nullptr;

    glm::mat4 m_view_matrix;
  };
}

#endif
