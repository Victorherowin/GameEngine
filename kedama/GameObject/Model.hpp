/*!
  \file Model.hpp
  \brief 模型类

  \date 2017.01.31
  \author KedamaOvO
*/

#ifndef _H_MODEL
#define _H_MODEL

#include "../Include.hpp"
#include "../Define.hpp"
#include "../RenderSystem/MeshRenderer.hpp"
#include "GameObject.hpp"

namespace Kedama {
  class KEDAMA_API Model:public GameObject
  {
  public:

  private:
    MeshRenderer* m_mesh_renderer=nullptr;

    //TODO:碰撞箱->bullet
  };
}

#endif
