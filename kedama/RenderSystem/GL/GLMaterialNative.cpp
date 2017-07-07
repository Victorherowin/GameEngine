#include "GLMaterialNative.hpp"
#include "Visitor/GLStd140UniformBlockSizeVisitor.inl"
#include "Visitor/GLStd140UniformBlockVisitor.inl"
namespace Kedama
{
    namespace GL
    {
        GLMaterialNative::GLMaterialNative()
        {
            glCreateBuffers(1, &m_ubo);
        }

        GLMaterialNative::~GLMaterialNative()
        {
            glUnmapNamedBuffer(m_ubo);
            glDeleteBuffers(1, &m_ubo);
        }

        void GLMaterialNative::Init(const list<AbstractPropertyValue*>& property_list)
        {
            GLStd140UniformBlockSizeVisitor size_visitor;
            for(auto&& pv:property_list)
            {
                pv->Accept(size_visitor);
            }

            int size =size_visitor.GetBlockSize();
            glNamedBufferStorage(m_ubo,size,nullptr,GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);
            m_ubo_memory=(uint8_t*)glMapNamedBufferRange(m_ubo,0,size,GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);

            GLStd140UniformBlockVisitor visitor(m_ubo_memory);
            for(auto&& pv:property_list)
            {
                pv->Accept(visitor);
            }
        }
    }
}
