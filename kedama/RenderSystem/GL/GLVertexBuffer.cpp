#include "GLVertexBuffer.hpp"

#include "GLVertexBuffer.inl"

namespace Kedama
{

  namespace detail
  {
    struct GLVertex
    {
      int16 m_position[3];
      int16 m_normal[3];
      uint16 m_uv[2];
      int16 m_tbn_quat[4];

      uint16 m_bone_index[4];
      uint8 m_weight[4];
    };

    GLVertex* Convert(vector<Vertex> &vertices)
    {
      GLVertex* tmp_vert=new GLVertex[vertices.size()];
      GLVertex* p_vert=tmp_vert;
      float tmp_weight[4];

      for(auto& vert:vertices)
        {
          FloatTo<vec3,int16>(vert.GetPositon(),p_vert->m_position);
          FloatTo<vec3,int16>(vert.GetNormal(),p_vert->m_normal);
          FloatTo<vec2,uint16>(vert.GetTextureCoord(),p_vert->m_uv);
          FloatTo<quat,int16>(vert.GetTBNQuaternion(),p_vert->m_tbn_quat);
          vert.GetBoneIndexAndWeight(p_vert->m_bone_index,tmp_weight);
          for(float& f:tmp_weight)
            p_vert->m_weight[&f-tmp_weight] = FloatTo<uint8>(f);
          ++p_vert;
        }
      return tmp_vert;
    }
  }

  GLVertexBuffer::GLVertexBuffer()
  {
    glGenBuffers(1,&m_vbo);
  }

  GLVertexBuffer::~GLVertexBuffer()
  {
    glDeleteBuffers(1,&m_vbo);
  }

  void GLVertexBuffer::Create(int32_t vertex_size,int32_t len,BufferUsage usage)
  {
    static GLenum __usage_table[]={GL_STATIC_DRAW,GL_STATIC_DRAW,GL_DYNAMIC_DRAW};

    m_usage=__usage_table[(int32_t)usage];
    glBindBuffer(GL_ARRAY_BUFFER,m_vbo);
    glBufferData(GL_ARRAY_BUFFER,vertex_size*len,nullptr,m_usage);
    glBindBuffer(GL_ARRAY_BUFFER,0);
  }

  void GLVertexBuffer::SendVertices(vector<Vertex> &vertices)
  {
    detail::GLVertex* tmp_vert=detail::Convert(vertices);
    glBindBuffer(GL_ARRAY_BUFFER,m_vbo);
    glBufferData(GL_ARRAY_BUFFER,sizeof(detail::GLVertex)*vertices.size(),tmp_vert,m_usage);
    glBindBuffer(GL_ARRAY_BUFFER,m_vbo);
    delete tmp_vert;
  }

  void GLVertexBuffer::SendSubVertices(vector<Vertex> &vertices,int32_t offset)
  {
    detail::GLVertex* tmp_vert=detail::Convert(vertices);
    glBindBuffer(GL_ARRAY_BUFFER,m_vbo);
    glBufferSubData(GL_ARRAY_BUFFER,offset*sizeof(detail::GLVertex),vertices.size(),tmp_vert);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    delete tmp_vert;
  }

  void GLVertexBuffer::SendData(void*data,int32_t type_size,int32_t len)
  {
    glBindBuffer(GL_ARRAY_BUFFER,m_vbo);
    glBufferData(GL_ARRAY_BUFFER,type_size*len,data,m_usage);
    glBindBuffer(GL_ARRAY_BUFFER,0);
  }

  void GLVertexBuffer::SendSubData(void* data,int32_t type_size,int32_t len,int32_t offset)
  {
    glBindBuffer(GL_ARRAY_BUFFER,m_vbo);
    glBufferSubData(GL_ARRAY_BUFFER,offset*type_size,len,data);
    glBindBuffer(GL_ARRAY_BUFFER,0);
  }

  void* GLVertexBuffer::MapBuffer(BufferAccess access)
  {
    static GLenum __table[]={GL_READ_ONLY,GL_WRITE_ONLY,GL_READ_WRITE};
    glBindBuffer(GL_ARRAY_BUFFER,m_vbo);
    void* p=glMapBuffer(GL_ARRAY_BUFFER,__table[(int32_t)access]);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    return p;
  }

  bool GLVertexBuffer::UnMapBuffer()
  {
    glBindBuffer(GL_ARRAY_BUFFER,m_vbo);
    bool ret=glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    return ret;
  }
}
