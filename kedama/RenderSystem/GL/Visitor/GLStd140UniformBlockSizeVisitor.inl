//
// Created by moe on 2017-07-04.
//

#ifndef KEDAMA_GLSTD140UNIFORMBLOCKSIZEVISITOR_INL
#define KEDAMA_GLSTD140UNIFORMBLOCKSIZEVISITOR_INL

#include "../../PropertyValue.hpp"
#include "../../PropertyValueVisitor.hpp"

#define DEFINE_VISIT_METHOD_WITHOUT_ALIGN(type,size) void Visit(PropertyValue<type>* pv) override{m_block_size+=size;}
#define DEFINE_VISIT_METHOD_2N(type,size) void Visit(PropertyValue<type>* pv) override{Align2N();m_block_size+=size;}
#define DEFINE_VISIT_METHOD_4N(type,size) void Visit(PropertyValue<type>* pv) override{Align4N();m_block_size+=size;}

#define DEFINE_VISIT_ARRAY_METHOD(type,size) void Visit(PropertyValueArray<type>* pv) override{Align4N();m_block_size+=size*pv->GetSize();}

namespace Kedama
{
    namespace GL
    {
        using namespace glm;

        class GLStd140UniformBlockSizeVisitor: public PropertyValueVisitor
        {

        public:
            inline size_t GetBlockSize()
            {return m_block_size;}

        private:
            DEFINE_VISIT_METHOD_WITHOUT_ALIGN(int32_t,4)
            DEFINE_VISIT_METHOD_WITHOUT_ALIGN(uint32_t,4)
            DEFINE_VISIT_METHOD_WITHOUT_ALIGN(float,4)
            DEFINE_VISIT_METHOD_WITHOUT_ALIGN(double,8)
            DEFINE_VISIT_METHOD_WITHOUT_ALIGN(bool,4)
            DEFINE_VISIT_METHOD_2N(vec2,8)
            DEFINE_VISIT_METHOD_4N(vec3,16)
            DEFINE_VISIT_METHOD_4N(vec4,16)
            DEFINE_VISIT_METHOD_2N(ivec2,8)
            DEFINE_VISIT_METHOD_4N(ivec3,16)
            DEFINE_VISIT_METHOD_4N(ivec4,16)
            DEFINE_VISIT_METHOD_2N(bvec2,8)
            DEFINE_VISIT_METHOD_4N(bvec3,16)
            DEFINE_VISIT_METHOD_4N(bvec4,16)
            DEFINE_VISIT_METHOD_2N(uvec2,8)
            DEFINE_VISIT_METHOD_4N(uvec3,16)
            DEFINE_VISIT_METHOD_4N(uvec4,16)
            DEFINE_VISIT_METHOD_4N(dvec2,16)
            DEFINE_VISIT_METHOD_4N(dvec3,32)
            DEFINE_VISIT_METHOD_4N(dvec4,32)

            DEFINE_VISIT_METHOD_4N(mat2,32)
            DEFINE_VISIT_METHOD_4N(mat3,48)
            DEFINE_VISIT_METHOD_4N(mat3x4,48)
            DEFINE_VISIT_METHOD_4N(mat4,64)

            //Array
            DEFINE_VISIT_ARRAY_METHOD(int32_t,16)
            DEFINE_VISIT_ARRAY_METHOD(uint32_t,16)
            DEFINE_VISIT_ARRAY_METHOD(float,16)
            DEFINE_VISIT_ARRAY_METHOD(double,16)
            DEFINE_VISIT_ARRAY_METHOD(bool,16)
            DEFINE_VISIT_ARRAY_METHOD(vec2,16)
            DEFINE_VISIT_ARRAY_METHOD(vec3,16)
            DEFINE_VISIT_ARRAY_METHOD(vec4,16)
            DEFINE_VISIT_ARRAY_METHOD(ivec2,16)
            DEFINE_VISIT_ARRAY_METHOD(ivec3,16)
            DEFINE_VISIT_ARRAY_METHOD(ivec4,16)
            DEFINE_VISIT_ARRAY_METHOD(bvec2,16)
            DEFINE_VISIT_ARRAY_METHOD(bvec3,16)
            DEFINE_VISIT_ARRAY_METHOD(bvec4,16)
            DEFINE_VISIT_ARRAY_METHOD(uvec2,16)
            DEFINE_VISIT_ARRAY_METHOD(uvec3,16)
            DEFINE_VISIT_ARRAY_METHOD(uvec4,16)
            DEFINE_VISIT_ARRAY_METHOD(dvec2,16)
            DEFINE_VISIT_ARRAY_METHOD(dvec3,32)
            DEFINE_VISIT_ARRAY_METHOD(dvec4,32)

            DEFINE_VISIT_ARRAY_METHOD(mat2,32)
            DEFINE_VISIT_ARRAY_METHOD(mat3,48)
            DEFINE_VISIT_ARRAY_METHOD(mat3x4,48)
            DEFINE_VISIT_ARRAY_METHOD(mat4,64)
        private:
            inline void Align4N()//4N
            {
                if(m_block_size&0xf)
                {
                    m_block_size&=0xfffffff0;
                    m_block_size+=16;
                }
            }

            inline void Align2N()//2N
            {
                if(m_block_size&0x7)
                {
                    m_block_size&=0xfffffff8;
                    m_block_size+=8;
                }
            }

            size_t m_block_size=0;

        };
    }
}

#undef DEFINE_VISIT_METHOD_WITHOUT_ALIGN
#undef DEFINE_VISIT_METHOD_2N
#undef DEFINE_VISIT_METHOD_4N

#undef DEFINE_VISIT_ARRAY_METHOD

#endif //KEDAMA_GLSTD140UNIFORMBLOCKSIZEVISITOR_INL
