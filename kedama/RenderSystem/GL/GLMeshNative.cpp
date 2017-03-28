#include "GLMeshNative.hpp"
#include "VertexConvert.inl"

#define POSITION_INDEX 0
#define NORMAL_INDEX 1
#define UV_INDEX 2
#define TBN_INDEX 3

namespace Kedama {
  template<typename T>
  inline size_t GetByteCount(T& v)
  {
    return v.size()*sizeof(typename T::value_type);
  }

  namespace GL {
    GLMeshNative::GLMeshNative()
    {
      glCreateVertexArrays(1,&vao);
    }

    GLMeshNative::~GLMeshNative()
    {
      glUnmapNamedBuffer(vbo);
      glUnmapNamedBuffer(ibo);
      glDeleteBuffers(1,&vbo);
      glDeleteBuffers(1,&ibo);
      glDeleteVertexArrays(1,&vao);
    }


    /// 1 position
    /// 2 normal
    /// 3 uvs
    /// 4 tangent
    void GLMeshNative::UploadVertices(const vector<vec3>& vertices)
    {
      if(m_old_vertices_num!=vertices.size())
      {
        if(vbo!=0)
          glDeleteBuffers(1,&vbo);

        m_old_vertices_num=vertices.size();

        uint32_t total_size=m_old_vertices_num*sizeof(vec3)*3+m_old_vertices_num*sizeof(vec2);

        glCreateBuffers(1,&vbo);
        glNamedBufferStorage(vbo,total_size,nullptr,GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);
        m_vbo_mem=(uint8_t*)glMapNamedBufferRange(vbo,0,total_size,GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);
        ApplyVBO();
      }

      memcpy(m_vbo_mem,vertices.data(),vertices.size()*sizeof(vec3));
    }

    void GLMeshNative::UploadIndices(const vector<uint32_t>& indices)
    {
      if(m_old_indices_num!=indices.size())
      {
        if(ibo!=0)
          glDeleteBuffers(1,&ibo);

        glCreateBuffers(1,&ibo);
        glNamedBufferStorage(ibo,indices.size()*sizeof(uint32_t),nullptr,GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);
        m_ibo_mem=(uint32_t*)glMapNamedBufferRange(ibo,0,indices.size()*sizeof(uint32_t),GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);
        m_old_indices_num=indices.size();
        ApplyIBO();
      }

      memcpy(m_ibo_mem,indices.data(),indices.size()*sizeof(uint32_t));
    }


    void GLMeshNative::UploadNormals(const vector<vec3>& normals)
    {
      memcpy(m_vbo_mem
             +m_old_vertices_num*sizeof(vec3),
             normals.data(),normals.size()*sizeof(vec3));
    }

    void GLMeshNative::UploadTangents(const vector<vec3>& tangents)
    {
      memcpy(m_vbo_mem
             +m_old_vertices_num*sizeof(vec3)
             +m_old_vertices_num*sizeof(vec3)
             +m_old_vertices_num*sizeof(vec2),
             tangents.data(),tangents.size()*sizeof(vec3));
    }

    void GLMeshNative::UploadUVs(const vector<vec2>& uvs)
    {
      memcpy(m_vbo_mem
             +m_old_vertices_num*sizeof(vec3)
             +m_old_vertices_num*sizeof(vec3),
             uvs.data(),uvs.size()*sizeof(vec2));
    }

    void GLMeshNative::ApplyVBO()
    {
      glVertexArrayVertexBuffer(vao,POSITION_INDEX,vbo,0,sizeof(vec3));
      glVertexArrayAttribBinding(vao,POSITION_INDEX,POSITION_INDEX);
      glVertexArrayAttribFormat(vao,POSITION_INDEX,3,GL_FLOAT,GL_FALSE,0);//position 0

      glVertexArrayVertexBuffer(vao,NORMAL_INDEX,vbo,0,sizeof(vec3));
      glVertexArrayAttribBinding(vao,NORMAL_INDEX,NORMAL_INDEX);
      glVertexArrayAttribFormat(vao,NORMAL_INDEX,3,GL_FLOAT,GL_FALSE,m_old_vertices_num*sizeof(vec3));//normal 1

      glVertexArrayVertexBuffer(vao,UV_INDEX,vbo,0,sizeof(vec2));
      glVertexArrayAttribBinding(vao,UV_INDEX,UV_INDEX);
      glVertexArrayAttribFormat(vao,UV_INDEX,2,GL_FLOAT,GL_FALSE,m_old_vertices_num*sizeof(vec3)*2);//uv 2

      glEnableVertexArrayAttrib(vao,POSITION_INDEX);
      glEnableVertexArrayAttrib(vao,UV_INDEX);
      glEnableVertexArrayAttrib(vao,NORMAL_INDEX);
    }

    void GLMeshNative::ApplyIBO()
    {
      glVertexArrayElementBuffer(vao,ibo);//ibo
    }
  }
}
