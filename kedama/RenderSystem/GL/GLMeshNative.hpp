#ifndef _H_MESHNATIVE
#define _H_MESHNATIVE

#include "../../Include.hpp"
#include "../Mesh.hpp"

namespace Kedama {
  namespace GL {
    class KEDAMA_API GLMeshNative:public Mesh::INative
    {
    public:
      GLMeshNative();
      ~GLMeshNative();
      void Upload(const Mesh& mesh)override;

    private:
      GLuint m_vao;
      GLuint m_vbo,m_ibo;
    };
  }
}

#endif
