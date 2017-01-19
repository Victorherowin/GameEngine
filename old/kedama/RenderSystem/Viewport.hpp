#ifndef VIEWPORT
#define VIEWPORT

#include "../Include.hpp"
#include "../Define.hpp"

namespace Kedama {

  class Viewport
  {
  public:
    void SetPerspective(float fov,float aspect,float near,float far);
    void SetOrtho(float left,float right,float buttom,float top);

    inline const glm::mat4& GetProjectionMatrix()
    {return m_projection_matrix;}

  private:
    glm::mat4 m_projection_matrix;
  };
}

#endif
