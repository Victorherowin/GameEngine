/*!
  \file RenderCommand
  \brief 渲染命令

  \date 2014.02.04
*/

#ifndef _H_RENDERCOMMAND_
#define _H_RENDERCOMMAND_

#include "../GameObject/Transform.hpp"
#include "Mesh.hpp"

namespace Kedama {

  struct RenderCommand
  {
    Transform* transform;
    Mesh* mesh;
    Material* material;
  };

  struct MergedRenderCommand
  {
    vector<Transform*> transforms;
    vector<Material*> materials;
    Mesh* mesh;
  };

  struct PostProcessCommand
  {
    Material* material;
  };
}

#endif
