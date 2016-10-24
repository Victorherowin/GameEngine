#include "GLVertexBuffer.hpp"

#include "GLVertexBuffer.inl"

namespace Kedama
{

  namespace detail
  {
    static GLenum __usage_table[]={GL_STATIC_DRAW,GL_STATIC_DRAW,GL_DYNAMIC_DRAW};

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
        memcpy(p_vert->m_bone_index,&vert.GetBoneIndex()[0],sizeof(uint16)*4);
        for(int i=0;i<4;++i)
        {
          p_vert->m_weight[i] = FloatTo<uint8>(vert.GetWeight()[i]);
        }
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
    Bind();

    if(m_usage==GL_DYNAMIC_DRAW&&m_maped_ptr!=nullptr)
    {
      glUnmapBuffer(GL_ARRAY_BUFFER);
      m_maped_ptr=nullptr;
    }

    m_usage=detail::__usage_table[(int32_t)usage];

    if(m_usage==GL_DYNAMIC_DRAW)
    {
      glBufferStorage(GL_ARRAY_BUFFER,vertex_size*len,nullptr,
                      GL_MAP_COHERENT_BIT|GL_MAP_PERSISTENT_BIT|GL_DYNAMIC_STORAGE_BIT|
                      GL_MAP_WRITE_BIT|GL_MAP_READ_BIT);
      m_maped_ptr=glMapBufferRange(GL_ARRAY_BUFFER,0,vertex_size*len ,GL_MAP_COHERENT_BIT|GL_MAP_PERSISTENT_BIT|
                                   GL_DYNAMIC_STORAGE_BIT|GL_MAP_WRITE_BIT|GL_MAP_READ_BIT);
    }
    else
    {
      glBufferData(GL_ARRAY_BUFFER,vertex_size*len,nullptr,m_usage);
    }
    Unbind();
  }

  void GLVertexBuffer::SendVertices(vector<Vertex> &vertices,BufferUsage usage)
  {
    Bind();

    if(m_usage==GL_DYNAMIC_DRAW&&m_maped_ptr!=nullptr)
    {
      glUnmapBuffer(GL_ARRAY_BUFFER);
      m_maped_ptr=nullptr;
    }

    GLVertex* tmp_vert=detail::Convert(vertices);
    m_usage=detail::__usage_table[(int32_t)usage];

    if(m_usage==GL_DYNAMIC_DRAW)
    {
      if(m_maped_ptr!=nullptr)
      {
        glUnmapBuffer(GL_ARRAY_BUFFER);
        m_maped_ptr=nullptr;
      }
      glBufferStorage(GL_ARRAY_BUFFER,vertices.size()*sizeof(GLVertex),tmp_vert,
                      GL_MAP_COHERENT_BIT|GL_MAP_PERSISTENT_BIT|GL_DYNAMIC_STORAGE_BIT|
                      GL_MAP_WRITE_BIT|GL_MAP_READ_BIT);
      m_maped_ptr=glMapBufferRange(GL_ARRAY_BUFFER,0,vertices.size()*sizeof(GLVertex),GL_MAP_COHERENT_BIT|
                                   GL_MAP_PERSISTENT_BIT|GL_DYNAMIC_STORAGE_BIT|GL_MAP_WRITE_BIT|
                                   GL_MAP_READ_BIT);
    }
    else
    {
      glBufferData(GL_ARRAY_BUFFER,sizeof(GLVertex)*vertices.size(),tmp_vert,m_usage);
    }
    Unbind();
    delete[] tmp_vert;
  }

  void GLVertexBuffer::SendSubVertices(vector<Vertex> &vertices,int32_t offset)
  {
    GLVertex* tmp_vert=detail::Convert(vertices);
    Bind();
    if(m_usage==GL_DYNAMIC_DRAW)
    {
      memcpy(((GLVertex*)m_maped_ptr)+offset,vertices.data(),vertices.size()*sizeof(GLVertex));
    }
    else
    {
      glBufferSubData(GL_ARRAY_BUFFER,offset*sizeof(GLVertex),vertices.size()*sizeof(GLVertex),tmp_vert);
    }
    Unbind();
    delete[] tmp_vert;
  }

  void GLVertexBuffer::SendData(void*data,int32_t len,BufferUsage usage)
  {
    Bind();
    if(m_usage==GL_DYNAMIC_DRAW&&m_maped_ptr!=nullptr)
    {
      glUnmapBuffer(GL_ARRAY_BUFFER);
      m_maped_ptr=nullptr;
    }

    m_usage=detail::__usage_table[(int32_t)usage];

    if(m_usage==GL_DYNAMIC_DRAW)
    {
      glBufferStorage(GL_ARRAY_BUFFER,len,data,
                      GL_MAP_COHERENT_BIT|GL_MAP_PERSISTENT_BIT|GL_DYNAMIC_STORAGE_BIT|
                      GL_MAP_WRITE_BIT|GL_MAP_READ_BIT);
      m_maped_ptr=glMapBufferRange(GL_ARRAY_BUFFER,0,len ,GL_MAP_COHERENT_BIT|GL_MAP_PERSISTENT_BIT|
                                   GL_DYNAMIC_STORAGE_BIT|GL_MAP_WRITE_BIT|GL_MAP_READ_BIT);
    }
    else
    {
      glBufferData(GL_ARRAY_BUFFER,len,data,m_usage);
    }
    Unbind();
  }

  void GLVertexBuffer::SendSubData(void* data,int32_t len,int32_t offset)
  {
    Bind();
    if(m_usage==GL_DYNAMIC_DRAW)
    {
      memcpy(((uint8_t*)m_maped_ptr)+offset,data,len);
    }
    else
    {
      glBufferSubData(GL_ARRAY_BUFFER,offset,len,data);
    }
    Unbind();
  }
}
