/*!
 * \file MeshRenderer.hpp
 * \brief 用于控制GameObject是否被渲染
 *
 * \author KedamaOvO
 * \version 0.0.1
 * \date 2017.01.26
 *
*/

#ifndef _H_MESHRENDERER
#define _H_MESHRENDERER

#include "Mesh.hpp"
#include "../Define.hpp"

namespace Kedama
{
  class KEDAMA_API MeshRenderer
  {
  public:
    inline void Enable(){m_enable=true;}
    inline void Disable(){m_enable=false;}
    inline bool Enabled(){return m_enable;}

    inline void SetDrawMode(DrawMode mode){m_draw_mode=mode;}

    inline void SetMesh(StaticMesh* mesh){m_mesh=mesh;}
    inline StaticMesh* GetMesh(){return m_mesh;}

  private:
    bool m_enable=true;
    DrawMode m_draw_mode=DrawMode::TRIANGLES;
    StaticMesh* m_mesh=nullptr;
    Material* material=nullptr;
  };


}

#endif
