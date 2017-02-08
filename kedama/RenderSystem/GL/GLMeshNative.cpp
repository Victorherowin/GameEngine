#include "GLMeshNative.hpp"
#include "VertexConvert.inl"

namespace Kedama {
  template<typename T>
  inline size_t GetByteCount(T& v)
  {
    return v.size()*sizeof(typename T::value_type);
  }

  namespace GL {
    GLMeshNative::GLMeshNative()
    {
      glGenBuffers(1,&m_vbo);
      glGenBuffers(1,&m_ibo);
      glGenVertexArrays(1,&m_vao);
    }

    GLMeshNative::~GLMeshNative()
    {
      glDeleteBuffers(1,&m_vbo);
      glDeleteBuffers(1,&m_ibo);
      glDeleteVertexArrays(1,&m_vao);
    }


    void GLMeshNative::Upload(const Mesh& mesh)
    {
      /*VertexConverter conv(m_mesh);
      pair<vec3,vec3> bound_box=conv.GetBoundSize();
      vector<u16vec3> vert=conv.GetVertices();
      vector<u8vec2> uvs=conv.GetUVs();
      vector<i16vec3> normals=conv.GetNormals();
      vector<quat> tbns=conv.GetTBNs();
*/ //TODO:顶点压缩优化

      size_t vert_size=GetByteCount(mesh.GetVertices());
      size_t uvs_size=GetByteCount(mesh.GetUVs());
      size_t normals_size=GetByteCount(mesh.GetNormals());
      //size_t tbns_size=GetByte(mesh->Get);
      size_t total_size=vert_size+uvs_size+normals_size;


      glNamedBufferStorage(m_vbo,total_size,nullptr,GL_MAP_WRITE_BIT);
      glNamedBufferStorage(m_ibo,GetByteCount(mesh.GetIndices()),nullptr,GL_MAP_WRITE_BIT);
      uint8_t* mvbo=(uint8_t*)glMapNamedBuffer(m_vbo,GL_STATIC_DRAW);
      uint8_t* mibo=(uint8_t*)glMapNamedBuffer(m_ibo,GL_STATIC_DRAW);

      //VBO
      memcpy(mvbo,mesh.GetVertices().data(),vert_size);
      mvbo+=vert_size;
      memcpy(mvbo,mesh.GetUVs().data(),uvs_size);
      mvbo+=uvs_size;
      memcpy(mvbo,mesh.GetNormals().data(),normals_size);
      mvbo+=normals_size;
      //memcpy(mvbo,tbns.data(),tbns_size);

      //IBO
      memcpy(mibo,mesh.GetIndices().data(),GetByteCount(mesh.GetIndices()));

      glUnmapNamedBuffer(m_vbo);
      glUnmapNamedBuffer(m_ibo);
    }
  }
}
