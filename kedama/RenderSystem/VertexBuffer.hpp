#ifndef VERTEXBUFFER
#define VERTEXBUFFER

#include <vector>

#include "../Config.hpp"
#include "Vertex.hpp"
#include "BufferEnum.hpp"

namespace Kedama
{
    struct VertexLayout
    {
        enum class ValueType
        {
            INT32,INT16,INT8,UINT32,UINT16,UINT8,FLOAT,HALF_FLAOT
        };

        static constexpr uint16_t UNUSEED=std::numeric_limits<uint16_t>::max();

        uint16_t position;
        uint16_t uv;
        uint16_t normal;
        uint16_t tbn;
        uint16_t bone_index;
        uint16_t weight;
        vector<tuple<ValueType,int/*size*/,int/*type*/,int/*stride*/,int/*offset*/,uint16_t>> custom;
    };

    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer(){}

        //创建一个空VertexBuffer
        virtual void Create(int vertex_size=4,int len=0,BufferUsage usage=BufferUsage::Default)=0;

        //发送顶点
        virtual void SendVertices(vector<Vertex>& vertices,BufferUsage usage)=0;
        virtual void SendSubVertices(vector<Vertex>& vertices,int offset)=0;
        virtual void SendData(void* data,int type_size,int len,BufferUsage usage)=0;
        virtual void SendSubData(void *data,int type_size,int len,int offset)=0;

        virtual void* MapBuffer(BufferAccess access){return nullptr;}
        virtual bool UnMapBuffer(){return false;}

        void SetVertexLayout(const VertexLayout& vl){use_vl=true;m_vl=vl;}
        inline const VertexLayout& GetVertexLayout(){return m_vl;}
        bool UseVertexLayout(){return use_vl;}
    private:
        bool use_vl=false;
        VertexLayout m_vl;
    };

    DEFINE_SHARED_PTR(VertexBuffer)
}

#endif
