#include "Mesh.hpp"

#include "../Engine.hpp"

namespace Kedama //BaseModel
{
  BaseModel::BaseModel(const string& name):GameObject(name)
  {
  }

  void BaseModel::AddMesh(Mesh &mb)
  {
    m_meshs.push_back(mb);
  }
}

namespace Kedama //DynamicModel
{
  DynamicModel::DynamicModel(const string &name):BaseModel(name)
  {

  }
}
