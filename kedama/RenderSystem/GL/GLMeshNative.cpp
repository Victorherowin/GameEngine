#include "GLMeshNative.hpp"
#include "VertexConvert.inl"

#define POSITION_INDEX 0
#define UV_INDEX 1
#define NORMAL_INDEX 2
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
      glCreateBuffers(1,&vbo);
      glCreateBuffers(1,&ibo);
      glCreateVertexArrays(1,&vao);
    }

    GLMeshNative::~GLMeshNative()
    {
      glDeleteBuffers(1,&vbo);
      glDeleteBuffers(1,&ibo);
      glDeleteVertexArrays(1,&vao);
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
      size_t indices_size=GetByteCount(mesh.GetIndices());


      glNamedBufferStorage(vbo,total_size,nullptr,GL_MAP_WRITE_BIT);
      glNamedBufferStorage(ibo,indices_size,nullptr,GL_MAP_WRITE_BIT);
      vec3* mvbo=(vec3*)glMapNamedBufferRange(vbo,0,total_size,GL_MAP_WRITE_BIT);
      vec3* mibo=(vec3*)glMapNamedBufferRange(ibo,0,indices_size,GL_MAP_WRITE_BIT);

      const vec3* p=mesh.GetVertices().data();

      //VBO
      memcpy(mvbo,p,vert_size);
      memcpy(mvbo+vert_size,mesh.GetUVs().data(),uvs_size);
      memcpy(mvbo+vert_size+uvs_size,mesh.GetNormals().data(),normals_size);
//      mvbo+=normals_size;
      //memcpy(mvbo,tbns.data(),tbns_size);

      //IBO
      memcpy(mibo,mesh.GetIndices().data(),indices_size);

      glUnmapNamedBuffer(vbo);
      glUnmapNamedBuffer(ibo);

      //VAO
      glVertexArrayElementBuffer(vao,ibo);//ibo

      glVertexArrayVertexBuffer(vao,POSITION_INDEX,vbo,0,sizeof(vec3));
      glVertexArrayAttribBinding(vao,POSITION_INDEX,POSITION_INDEX);
      glVertexArrayAttribFormat(vao,POSITION_INDEX,3,GL_FLOAT,GL_FALSE,0);//position 0

      glVertexArrayVertexBuffer(vao,UV_INDEX,vbo,0,sizeof(vec2));
      glVertexArrayAttribBinding(vao,UV_INDEX,UV_INDEX);
      glVertexArrayAttribFormat(vao,UV_INDEX,2,GL_FLOAT,GL_FALSE,vert_size);//uv 1

      glVertexArrayVertexBuffer(vao,NORMAL_INDEX,vbo,0,sizeof(vec3));
      glVertexArrayAttribBinding(vao,NORMAL_INDEX,NORMAL_INDEX);
      glVertexArrayAttribFormat(vao,NORMAL_INDEX,3,GL_FLOAT,GL_FALSE,vert_size+uvs_size);//normal 2

      glEnableVertexArrayAttrib(vao,POSITION_INDEX);
      glEnableVertexArrayAttrib(vao,UV_INDEX);
      glEnableVertexArrayAttrib(vao,NORMAL_INDEX);
    }
  }
}
