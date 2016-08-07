#include "GLVertexBuffer.hpp"

#include "GLVertexBuffer.inl"

namespace Kedama
{

  namespace detail
  {
    GLVertex* Convert(vector<Vertex> &vertices)
    {
      GLVertex* tmp_vert=new GLVertex[vertices.size()];
      GLVertex* p_vert=tmp_vert;
      float tmp_weight[4];

      for(auto& vert:vertices)
      {
        memcpy(p_vert->m_position,&vert.GetPositon()[0],sizeof(float)*3);
        //FloatTo<vec3,int16>(vert.GetPositon(),p_vert->m_position);
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

  void GLVertexBuffer::Bind()
  {
    glBindBuffer(GL_ARRAY_BUFFER,m_vbo);
  }

  void GLVertexBuffer::Unbind()
  {
    glBindBuffer(GL_ARRAY_BUFFER,0);
  }

  void GLVertexBuffer::Create(int32_t vertex_size,int32_t len,BufferUsage usage)
  {
    static GLenum __usage_table[]={GL_STATIC_DRAW,GL_STATIC_DRAW,GL_DYNAMIC_DRAW};

    m_usage=__usage_table[(int32_t)usage];
    Bind();
    glBufferData(GL_ARRAY_BUFFER,vertex_size*len,nullptr,m_usage);
    Unbind();
  }

  void GLVertexBuffer::SendVertices(vector<Vertex> &vertices)
  {
    GLVertex* tmp_vert=detail::Convert(vertices);
    Bind();
    glBufferData(GL_ARRAY_BUFFER,sizeof(GLVertex)*vertices.size(),tmp_vert,m_usage);
    Unbind();
    delete tmp_vert;
  }

  void GLVertexBuffer::SendSubVertices(vector<Vertex> &vertices,int32_t offset)
  {
    GLVertex* tmp_vert=detail::Convert(vertices);
    Bind();
    glBufferSubData(GL_ARRAY_BUFFER,offset*sizeof(GLVertex),vertices.size(),tmp_vert);
    Unbind();
    delete tmp_vert;
  }

  void GLVertexBuffer::SendData(void*data,int32_t type_size,int32_t len)
  {
    Bind();
    glBufferData(GL_ARRAY_BUFFER,type_size*len,data,m_usage);
    Unbind();
  }

  void GLVertexBuffer::SendSubData(void* data,int32_t type_size,int32_t len,int32_t offset)
  {
    Bind();
    glBufferSubData(GL_ARRAY_BUFFER,offset*type_size,len,data);
    Unbind();
  }

  void* GLVertexBuffer::MapBuffer(BufferAccess access)
  {
    static GLenum __table[]={GL_READ_ONLY,GL_WRITE_ONLY,GL_READ_WRITE};
    Bind();
    void* p=glMapBuffer(GL_ARRAY_BUFFER,__table[(int32_t)access]);
    Unbind();
    return p;
  }

  bool GLVertexBuffer::UnMapBuffer()
  {
    Bind();
    bool ret=glUnmapBuffer(GL_ARRAY_BUFFER);
    Unbind();
    return ret;
  }
}
