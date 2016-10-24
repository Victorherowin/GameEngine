#include "Batch.hpp"

namespace Kedama {

  void Batch::AddModelInstance(GameObjectPtr& obj)
  {
    m_instancies.push_back(obj);
  }

  void Batch::SetModelMesh(const ModelMeshes &model)
  {
    m_model_mesh=model;
  }
}
