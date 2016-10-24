#ifndef BATCH
#define BATCH

#include "Mesh.hpp"

#include "../Include.hpp"
#include "../GameObject/GameObject.hpp"

namespace Kedama {

  class Batch
  {
  public:

    void SetModelMesh(const ModelMeshes& model);
    void AddModelInstance(GameObjectPtr& obj);

    inline const ModelMeshes GetModelMesh()const{return m_model_mesh;}
    inline const list<GameObjectPtr> GetInstancies()const{return m_instancies;}
  private:
    ModelMeshes m_model_mesh;
    list<GameObjectPtr> m_instancies;
  };

}
#endif
