//
// Created by moe on 2017-05-29.
//

#include "GLMeshBuffer.hpp"

namespace Kedama {
    namespace GL {
        GLBaseMeshBuffer::GLBaseMeshBuffer(size_t vertex_num,size_t index_num):m_vertex_num(vertex_num),m_index_num(index_num)
        {
            glCreateVertexArrays(1,&m_vao);
            glVertexArrayElementBuffer(m_vao,m_ibo);
        }

        GLBaseMeshBuffer::~GLBaseMeshBuffer() {
            glDeleteVertexArrays(1,&m_vao);
            glDeleteBuffers(m_vbos.size(),m_vbos.data());
        }

        GLuint GLBaseMeshBuffer::CreateVBO() {
            GLuint vbo;
            glCreateBuffers(1,&vbo);
            m_vbos.push_back(vbo);
            return vbo;
        }
    }
}

namespace Kedama {
    namespace GL {
        static int _type_size_table[]={1,2,4,1,2,4,4,4};

        GLMeshBuffer::GLMeshBuffer(size_t vertex_num,size_t index_num):GLBaseMeshBuffer(vertex_num,index_num) {
            glNamedBufferStorage(m_ibo,m_index_num*sizeof(GLuint),nullptr,GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);
            IBOMapAddress=(uint32_t*)glMapNamedBufferRange(m_ibo,0,index_num*sizeof(GLuint),GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);
        }

        void GLMeshBuffer::AddVertexAttribute(const string &attr_name, uint32_t location, DataType type, size_t size,size_t bytes) {
            static GLenum _gltype_table[]={GL_BYTE, GL_SHORT, GL_INT, GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT, GL_UNSIGNED_INT, GL_FLOAT, GL_UNSIGNED_INT_10_10_10_2};

            GLVertexAttribute va;
            va.AttributeName=attr_name;
            va.Location=location;
            va.Type=type;
            va.Size=size;
            va.Bytes=bytes;
            va.VBO=CreateVBO();


            glNamedBufferStorage(va.VBO,va.Bytes,nullptr,GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);
            if(va.VBOMappingAddress==nullptr)
                va.VBOMappingAddress=(uint8_t*)glMapNamedBufferRange(va.VBO,0,va.Bytes,GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);

            m_vertex_attribute[attr_name]=va;

            glVertexArrayVertexBuffer(m_vao,location,va.VBO,0,va.Size*_type_size_table[(int)type]);
            glVertexArrayAttribFormat(m_vao,location,size,_gltype_table[(int)type],GL_FALSE,0);
            glVertexArrayAttribBinding(m_vao,location,location);

            glEnableVertexArrayAttrib(m_vao,location);
        }

        void GLMeshBuffer::UpdateVertexAttribute(const string &attr_name, void *data) {

            GLVertexAttribute& va=m_vertex_attribute[attr_name];

            memcpy(va.VBOMappingAddress,data,va.Bytes);
        }

        void GLMeshBuffer::UpdateIndices(uint32_t *indices) {
            memcpy(IBOMapAddress,indices,m_index_num*sizeof(GLuint));
        }

        GLMeshBuffer::~GLMeshBuffer()
        {
            for(auto& va : m_vertex_attribute)
                if(va.second.VBOMappingAddress!=nullptr)
                    glUnmapNamedBuffer(va.second.VBO);
        }
    }
}