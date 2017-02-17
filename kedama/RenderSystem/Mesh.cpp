#include "Mesh.hpp"
#include "../Engine.hpp"
namespace Kedama {
  Mesh::Mesh()
  {
    m_native=Engine::GetSingleton().GetRendererFactory()->CreateMeshNative();
  }

  Mesh::~Mesh()
  {
    delete m_native;
  }

  void Mesh::Update()
  {
    m_native->Upload(*this);
  }
}
