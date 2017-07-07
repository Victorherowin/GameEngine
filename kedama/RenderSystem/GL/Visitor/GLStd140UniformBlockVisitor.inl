//
// Created by moe on 2017-07-05.
//

#ifndef KEDAMA_GLSTD140UNIFORMBLOCKVISITOR_INL
#define KEDAMA_GLSTD140UNIFORMBLOCKVISITOR_INL

#include "../../PropertyValue.hpp"
#include "../../PropertyValueVisitor.hpp"

#define DEFINE_VISIT_METHOD_WITHOUT_ALIGN(type,size) \
void Visit(PropertyValue<type>* pv) override\
{\
	memcpy(m_ubo_pointer+m_offset,pv->GetValueData(),sizeof(type));\
	pv->AddValueChangedListener([offset=m_offset,p=m_ubo_pointer](const AbstractPropertyValue& pv){\
            memcpy(p+offset,pv.GetValueData(),sizeof(type));\
        });\
	m_offset+=size;\
}


#define DEFINE_VISIT_METHOD_2N(type,size) \
void Visit(PropertyValue<type>* pv) override\
{\
	Align2N();\
	memcpy(m_ubo_pointer+m_offset,pv->GetValueData(),sizeof(type));\
	pv->AddValueChangedListener([offset=m_offset,p=m_ubo_pointer](const AbstractPropertyValue& pv){\
            memcpy(p+offset,pv.GetValueData(),sizeof(type));\
        });\
	m_offset+=size;\
}

#define DEFINE_VISIT_METHOD_4N(type,size) \
void Visit(PropertyValue<type>* pv) override\
{\
	Align4N();\
	memcpy(m_ubo_pointer+m_offset,pv->GetValueData(),sizeof(type));\
	pv->AddValueChangedListener([offset=m_offset,p=m_ubo_pointer](const AbstractPropertyValue& pv){\
            memcpy(p+offset,pv.GetValueData(),sizeof(type));\
        });\
	m_offset+=size;\
}

#define DEFINE_VISIT_ARRAY_METHOD(type,size)\
void Visit(PropertyValueArray<type>* pv) override\
{\
    Align4N();\
	for(size_t i=0;i<pv->GetSize();++i)\
	{\
		memcpy(m_ubo_pointer+m_offset+size*i,(*pv)[i].GetPointer(),sizeof(type));\
	}\
    pv->AddElementChangedListener([p=m_ubo_pointer,offset=m_offset](int position,const PropertyValueArray<type>& pva){\
        memcpy(p+offset+size*position,pva[position].GetPointer(),sizeof(type));\
    });\
    m_offset+=size*pv->GetSize();\
}

namespace Kedama
{
    namespace GL
    {
        using namespace glm;

        class GLStd140UniformBlockVisitor: public PropertyValueVisitor
        {
        public:
            GLStd140UniformBlockVisitor(uint8_t* ubo_pointer):m_ubo_pointer(ubo_pointer){}

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
                if(m_offset&0xf)
                {
                    m_offset&=0xfffffff0;
                    m_offset+=16;
                }
            }

            inline void Align2N()//2N
            {
                if(m_offset&0x7)
                {
                    m_offset&=0xfffffff8;
                    m_offset+=8;
                }
            }
            uint32_t m_offset=0;
            uint8_t* m_ubo_pointer;
        };
    }
}

#undef DEFINE_VISIT_METHOD_WITHOUT_ALIGN
#undef DEFINE_VISIT_METHOD_2N
#undef DEFINE_VISIT_METHOD_4N

#undef DEFINE_VISIT_ARRAY_METHOD

#endif //KEDAMA_GLSTD140UNIFORMBLOCKVISITOR_INL
