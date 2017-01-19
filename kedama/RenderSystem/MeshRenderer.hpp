#ifndef _H_MESHRENDERER
#define _H_MESHRENDERER

#include "Mesh.hpp"
#include "../Define.hpp"

namespace Kedama
{
  //TODO：更新,上传Mesh到绘图API
  class KEDAMA_API MeshRenderer
  {
  public:
    virtual ~MeshRenderer(){}
    inline void Enable(){m_enable=true;}
    inline void Disable(){m_enable=false;}
    inline bool Enabled(){return m_enable;}

  protected:
    bool m_enable=true;

  };


}

#endif
