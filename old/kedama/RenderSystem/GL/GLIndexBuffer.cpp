#include "GLIndexBuffer.hpp"

namespace Kedama
{
  GLIndexBuffer::GLIndexBuffer()
  {
    glGenBuffers(1,&m_ibo);
  }

  GLIndexBuffer::~GLIndexBuffer()
  {
    glDeleteBuffers(1,&m_ibo);
  }

  void GLIndexBuffer::Create(int32_t len)
  {
    Bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,len,nullptr,GL_STATIC_DRAW);
    Unbind();
  }

  void GLIndexBuffer::Bind()
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_ibo);
  }

  void GLIndexBuffer::Unbind()
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
  }

  void GLIndexBuffer::SendIndices(vector<uint32_t> &indices)
  {
    m_size=indices.size();
    Bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,indices.size()*sizeof(uint32_t),indices.data(),GL_STATIC_DRAW);
    Unbind();
  }

  void GLIndexBuffer::SendSubIndices(vector<uint32_t> &indices, int32_t offset, int32_t len)
  {
    if(offset>m_size)m_size+=len;
    if(offset<m_size&&offset+len>m_size)m_size=len+offset;
    Bind();
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER,offset*sizeof(uint32_t),len,indices.data());
    Unbind();
  }
}
