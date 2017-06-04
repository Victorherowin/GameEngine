#ifndef ASSETMANAGER
#define ASSETMANAGER

#include "Include.hpp"
#include "Define.hpp"

#include "RenderSystem/Mesh.hpp"

namespace Kedama
{
  using namespace std;
  class KEDAMA_API AssetManager
  {
  public:
    StaticMesh* CreateStaticMesh(const string& name);

    StaticMesh* GetStaticMesh(const string& name);
  private:
    map<string,StaticMesh*> m_mesh_map;
  };
}

#endif
