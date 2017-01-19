#ifndef ASSETMANAGER
#define ASSETMANAGER

#include "Include.hpp"
#include "Define.hpp"

#include "RenderSystem/Mesh.hpp"

namespace Kedama
{
  using namespace std;
  class AssetManager
  {
  public:
    void AddMesh(const string& name,Mesh* mesh);
    Mesh* CreateMesh(const string& name);
    Mesh* GetMesh(const string& name);
  private:
    map<string,Mesh*> m_mesh_map;
  };
}

#endif
