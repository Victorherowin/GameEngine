//
// Created by moe on 2017-06-02.
//

#ifndef KEDAMA_IMESHBUFFER_HPP
#define KEDAMA_IMESHBUFFER_HPP

#include "../../Include.hpp"
#include "../../GLMInclude.hpp"
#include "../../Define.hpp"

namespace Kedama {
    using namespace std;
    using namespace glm;
    enum class DataType {
        BYTE, SHORT, INT, UBYTE, USHORT, UINT, FLOAT, UINT_10_10_10_2
    };

    class KEDAMA_API IAbstractMeshBuffer
    {
    public:
        virtual ~IAbstractMeshBuffer() {}
    };

    ///@brief 可变大小的MeshBuffer
    class KEDAMA_API IMutableMeshBuffer : public virtual IAbstractMeshBuffer
    {
    public:

        virtual void AddVertexAttribute(const string &attr_name, uint32_t location, DataType type, size_t size)=0;
        virtual void UpdateVertexAttribute(const string &attr_name, void *data, size_t bytes)=0;
        virtual void UpdateIndices(uint32_t *indices, size_t num)=0;
    };

    ///@brief 固定大小的MeshBuffer
    class KEDAMA_API IMeshBuffer : public virtual IAbstractMeshBuffer
    {
    public:
        virtual ~IMeshBuffer() {}

        virtual void AddVertexAttribute(const string &attr_name, uint32_t location, DataType type, size_t size, size_t bytes)=0;
        virtual void UpdateVertexAttribute(const string &attr_name, void *data)=0;
        virtual void UpdateIndices(uint32_t *indices)=0;
    };
}

#endif //KEDAMA_IMESHBUFFER_HPP
