#ifndef _H_MODEL
#define _H_MODEL

#include "../Include.hpp"
#include "../Define.hpp"
#include "../RenderSystem/MeshRenderer.hpp"

namespace Kedama {
  class KEDAMA_API Model
  {
  public:

  private:
    MeshRenderer* m_mesh_renderer=nullptr;
    //TODO:碰撞箱
  };
}

#endif
