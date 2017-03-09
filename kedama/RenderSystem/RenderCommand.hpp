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
    Material* material;
    Mesh* mesh;
    int offset=0;
    int count=-1;
  };

  struct MergedRenderCommand
  {
    vector<Transform*> transforms;
    Material* material;
    Mesh* mesh;
    int offset=0;
    int count=-1;
  };

  struct PostProcessCommand
  {
    Material* material;
  };
}

#endif
