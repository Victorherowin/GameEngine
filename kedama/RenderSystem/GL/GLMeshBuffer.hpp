//
// Created by moe on 2017-05-29.
//

#ifndef KEDAMA_GLMESHBUFFER_HPP
#define KEDAMA_GLMESHBUFFER_HPP

#include <GL/glew.h>
#include "../../Define.hpp"
#include "../Mesh.hpp"
#include "utility/GLSmartObject.hpp"
#include "../Interface/IMeshBuffer.hpp"

namespace Kedama {
    namespace GL {

        class KEDAMA_API GLBaseMeshBuffer:public virtual IAbstractMeshBuffer {
        public:
            GLBaseMeshBuffer(size_t vertex_num=0,size_t index_num=0);

            virtual ~GLBaseMeshBuffer();

            inline GLSharedBuffer &GetIBO() { return m_ibo; }

            inline const vector<GLuint> &GetVBOs() const { return m_vbos; }

            inline GLuint GetVAO()const { return m_vao; }

            inline size_t GetVertexNumber()const{return m_vertex_num;}
            inline size_t GetIndexNumber()const{return m_index_num;}

            GLuint CreateVBO();

        protected:
            size_t m_vertex_num = 0;
            size_t m_index_num=0;

            GLuint m_vao;
            vector<GLuint> m_vbos;
            GLSharedBuffer m_ibo;
        };

        class KEDAMA_API GLMeshBuffer : public IMeshBuffer, public GLBaseMeshBuffer {
        public:
            struct GLVertexAttribute {
                string AttributeName;
                uint32_t Location = 0;
                DataType Type;
                size_t Size = 0;//vec 1 2 3 4
                size_t Bytes = 0;
                GLuint VBO = 0;
                uint8_t *VBOMappingAddress = nullptr;
            };
        public:
            GLMeshBuffer(size_t vertex_num,size_t index_num);

            ~GLMeshBuffer();

            void AddVertexAttribute(const string &attr_name, uint32_t location, DataType type, size_t size,
                                    size_t bytes) override;

            void UpdateVertexAttribute(const string &attr_name, void *data) override;

            void UpdateIndices(uint32_t *indices) override;

        private:
            uint32_t* IBOMapAddress=nullptr;
            map<string, GLVertexAttribute> m_vertex_attribute;
        };
    }
}


#endif //KEDAMA_GLMESHBUFFER_HPP
