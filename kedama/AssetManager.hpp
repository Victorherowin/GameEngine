#ifndef ASSETMANAGER
#define ASSETMANAGER

#include "Include.hpp"
#include "Define.hpp"

#include "RenderSystem/Mesh.hpp"
#include "RenderSystem/Material.hpp"
#include "RenderSystem/IIndexBuffer.hpp"
#include "RenderSystem/VertexBuffer.hpp"

namespace Kedama
{
  using namespace std;
  class AssetManager
  {
  public:
    Mesh* CreateMesh(const string& name,IIndexBufferPtr& ibo,VertexBufferPtr& vbo);
    void CreateMaterial();
  private:
    map<string,Mesh> m_meshes;
  };
}

#endif
