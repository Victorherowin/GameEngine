#ifndef _H_ISKINNER
#define _H_ISKINNER

#include "../RenderSystem/Mesh.hpp"

namespace Kedama {
  class ISkinner
  {
  public:
    virtual ~ISkinner(){}
    virtual void Skinning()=0;
    virtual IAbstractMeshBuffer* GetSkinedMesh()=0;
  };
}

#endif
