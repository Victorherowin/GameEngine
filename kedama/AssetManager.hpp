#ifndef ASSETMANAGER
#define ASSETMANAGER

#include "Include.hpp"
#include "Define.hpp"

#include "RenderSystem/Model.hpp"

namespace Kedama
{
  using namespace std;
  class KEDAMA_API AssetManager
  {
  public:
    StaticModel* LoadStaticModel(const string& name);

    StaticModel* GetStaticModel(const string& name);
  private:
    map<string,StaticMesh*> m_mesh_map;
  };
}

#endif
