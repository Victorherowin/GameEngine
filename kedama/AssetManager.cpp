#include "AssetManager.hpp"

#define CHECK_EXIST(type,map,id) if((map).find((id))==(map).end())throw std::runtime_error(#type"名已存在");

namespace Kedama
{
  void AssetManager::AddMesh(const string &name, Mesh *mesh)
  {
    CHECK_EXIST(Mesh,m_mesh_map,name)
    m_mesh_map[name]=mesh;
  }

  Mesh* AssetManager::CreateMesh(const string &name)
  {
    CHECK_EXIST(Mesh,m_mesh_map,name);
    Mesh* mesh=new Mesh;
    m_mesh_map[name]=mesh;
    return mesh;
  }

  Mesh* AssetManager::GetMesh(const string &name)
  {
    auto it=m_mesh_map.find(name);
    if(it!=m_mesh_map.end())return it->second;
    else throw runtime_error("Not Found");
  }
}
