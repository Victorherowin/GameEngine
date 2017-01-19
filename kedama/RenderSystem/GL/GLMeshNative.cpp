#include "GLMeshNative.hpp"
#include "VertexConvert.inl"

namespace Kedama {
  template<typename T>
  inline size_t GetByte(T& v)
  {
    return v.size()*sizeof(T::value_type);
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


    void GLMeshNative::Upload()
    {
      VertexConverter conv(m_mesh);
      pair<vec3,vec3> bound_box=conv.GetBoundSize();
      vector<u16vec3> vert=conv.GetVertices();
      vector<u8vec2> uvs=conv.GetUVs();
      vector<i16vec3> normals=conv.GetNormals();
      vector<quat> tbns=conv.GetTBNs();

      size_t vert_size=GetByte(vert);
      size_t uvs_size=GetByte(uvs);
      size_t normals_size=GetByte(normals);
      size_t tbns_size=GetByte(tbns);
      size_t total_size=vert_size+uvs_size+normals_size+tbns_size;

      glNamedBufferStorage(m_vbo,total_size,nullptr,GL_MAP_WRITE_BIT);
      uint8_t* mvbo=(uint8_t*)glMapNamedBuffer(m_vbo,GL_STATIC_DRAW);
      memcpy(mvbo,vert.data(),vert_size);
      mvbo+=vert_size;
      memcpy(mvbo,uvs.data(),uvs_size);
      mvbo+=uvs_size;
      memcpy(mvbo,normals.data(),normals_size);
      mvbo+=normals_size;
      memcpy(mvbo,tbns.data(),tbns_size);

      glUnmapNamedBuffer(m_vbo);
    }
  }
}
