#include "Mesh.hpp"

#include "../Engine.hpp"

namespace Kedama //BaseModel
{
  BaseModelPtr BaseModel::CreateBaseModel(const string &name)
  {
    return std::make_shared<BaseModel>(name);
  }

  BaseModel::BaseModel(const string& name):GameObject(name)
  {
  }

  void BaseModel::AddMesh(const MeshBuffer &mb,MaterialPtr& material,uint32_t offset)
  {
    Mesh m={mb,material,offset};
    m_meshs.push_back(m);
  }
}

namespace Kedama //DynamicModel
{
  DynamicModelPtr DynamicModel::CreateDynamicModel(const string &name)
  {
    return std::unique_ptr<DynamicModel>(new DynamicModel(name));
  }

  DynamicModel::DynamicModel(const string &name):BaseModel(name)
  {

  }
}
