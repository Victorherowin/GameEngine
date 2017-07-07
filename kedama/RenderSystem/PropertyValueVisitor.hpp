//
// Created by moe on 2017-07-04.
//

#ifndef KEDAMA_PROPERTYVALUEVISITOR_HPP
#define KEDAMA_PROPERTYVALUEVISITOR_HPP

#include "../GLMInclude.hpp"
#include "Interface/ITexture.hpp"

#define STATEMENT_VISITOR_METHOD(type) \
virtual void Visit(Kedama::PropertyValue<type>* pv);\
virtual void Visit(Kedama::PropertyValueArray<type>* pv);

namespace Kedama
{
    using namespace glm;

    template <typename T>class PropertyValue;
    template <typename T>class PropertyValueArray;

    class PropertyValueVisitor
    {
    public:
        STATEMENT_VISITOR_METHOD(int32_t)
        STATEMENT_VISITOR_METHOD(uint32_t)
        STATEMENT_VISITOR_METHOD(float)
        STATEMENT_VISITOR_METHOD(double)
        STATEMENT_VISITOR_METHOD(bool)
        STATEMENT_VISITOR_METHOD(vec2)
        STATEMENT_VISITOR_METHOD(vec3)
        STATEMENT_VISITOR_METHOD(vec4)
        STATEMENT_VISITOR_METHOD(ivec2)
        STATEMENT_VISITOR_METHOD(ivec3)
        STATEMENT_VISITOR_METHOD(ivec4)
        STATEMENT_VISITOR_METHOD(bvec2)
        STATEMENT_VISITOR_METHOD(bvec3)
        STATEMENT_VISITOR_METHOD(bvec4)
        STATEMENT_VISITOR_METHOD(uvec2)
        STATEMENT_VISITOR_METHOD(uvec3)
        STATEMENT_VISITOR_METHOD(uvec4)
        STATEMENT_VISITOR_METHOD(dvec2)
        STATEMENT_VISITOR_METHOD(dvec3)
        STATEMENT_VISITOR_METHOD(dvec4)
        STATEMENT_VISITOR_METHOD(mat2)
        STATEMENT_VISITOR_METHOD(mat3)
        STATEMENT_VISITOR_METHOD(mat3x4)
        STATEMENT_VISITOR_METHOD(mat4)

        STATEMENT_VISITOR_METHOD(ITexture2DArray*)
        STATEMENT_VISITOR_METHOD(ITexture2D*)
        STATEMENT_VISITOR_METHOD(ITextureCube*)
        STATEMENT_VISITOR_METHOD(ITextureCubeArray*)
        STATEMENT_VISITOR_METHOD(ITexture3D*)
    };
}
#endif //KEDAMA_PROPERTYVALUEVISITOR_HPP
