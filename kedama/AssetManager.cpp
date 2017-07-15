#include "AssetManager.hpp"

/*#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
*/
#define CHECK_EXIST(type,map,id) if((map).find((id))==(map).end())throw std::runtime_error(#type"名已存在");

namespace Kedama
{
  StaticModel* AssetManager::LoadStaticModel(const string &name)
  {
    /*CHECK_EXIST(Mesh,m_mesh_map,name);
    StaticMesh* mesh=new StaticMesh();
    m_mesh_map[name]=mesh;
    return mesh;*/
	  return new StaticModel();
  }

/*  StaticMesh* AssetManager::GetStaticMesh(const string &name)
  {
    auto it=m_mesh_map.find(name);
    if(it!=m_mesh_map.end())return it->second;
    else throw runtime_error("Not Found");
  }*/
}
