#ifndef _H_MESHNATIVE
#define _H_MESHNATIVE

#include "../../Include.hpp"
#include "../Mesh.hpp"
#include <GL/glew.h>

namespace Kedama {
  namespace GL {
    class KEDAMA_API GLMeshNative:public Mesh::INative
    {
    public:
      GLMeshNative();
      ~GLMeshNative();
      void Upload(const Mesh& mesh)override;

      GLuint vao;
      GLuint vbo=0,ibo=0;

    private:
      int m_lase_vertex_size=0,m_lase_indices_size=0;
    };
  }
}

#endif
