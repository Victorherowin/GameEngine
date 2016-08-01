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
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,len,nullptr,GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    }

    void GLIndexBuffer::SendIndices(vector<uint32_t> &indices)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,indices.size(),indices.data(),GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    }

    void GLIndexBuffer::SendSubIndices(vector<uint32_t> &indices, int32_t offset, int32_t len)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_ibo);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER,offset*sizeof(uint32_t),len,indices.data());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    }
}
