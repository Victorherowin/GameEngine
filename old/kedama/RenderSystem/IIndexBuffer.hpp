#ifndef IINDEXBUFFER
#define IINDEXBUFFER

#include <vector>

#include "Vertex.hpp"
#include "BufferEnum.hpp"

namespace Kedama
{
    using std::vector;

    class IIndexBuffer
    {
    public:
	virtual ~IIndexBuffer(){}

	//创建一个空IndexBuffer
	virtual void Create(int len)=0;

	//发送索引
	virtual void SendIndices(vector<uint32>& indices)=0;
	virtual void SendSubIndices(vector<uint32>& indices,int offset,int len)=0;
    };
}

#endif
