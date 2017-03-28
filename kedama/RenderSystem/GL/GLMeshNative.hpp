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
      void UploadIndices(const vector<uint32_t>& uvs)override final;
      void UploadVertices(const vector<vec3>& vertices)override final;
      void UploadNormals(const vector<vec3>& normals)override final;
      void UploadTangents(const vector<vec3>& tangents)override final;
      void UploadUVs(const vector<vec2>& uvs)override final;


      GLuint vao;
      GLuint vbo=0,ibo=0;

    private:
      void ApplyVBO();
      void ApplyIBO();
    private:
      int m_old_vertices_num=0,m_old_indices_num=0;
      uint8_t* m_vbo_mem=nullptr;
      uint32_t* m_ibo_mem=nullptr;
    };
  }
}

#endif
