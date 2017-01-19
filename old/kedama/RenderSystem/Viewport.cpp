#include "Viewport.hpp"

namespace Kedama {
  void Viewport::SetPerspective(float fov, float aspect, float near, float far)
  {
    m_projection_matrix=glm::perspective(fov,aspect,near,far);
  }

  void Viewport::SetOrtho(float left,float right,float buttom,float top)
  {
    m_projection_matrix=glm::ortho(left,right,buttom,top);
  }


}
