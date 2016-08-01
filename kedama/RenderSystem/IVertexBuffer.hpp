#ifndef IVERTEXBUFFER
#define IVERTEXBUFFER

#include <vector>

#include "Vertex.hpp"
#include "BufferEnum.hpp"

namespace Kedama
{
    using std::vector;

    class IVertexBuffer
    {
    public:
	virtual ~IVertexBuffer(){}

	//创建一个空VertexBuffer
	virtual void Create(int vertex_size=4,int len=0,BufferUsage usage=BufferUsage::Default)=0;

	//发送顶点
	virtual void SendVertices(vector<Vertex>& vertices)=0;
	virtual void SendSubVertices(vector<Vertex>& vertices,int offset)=0;
	virtual void SendData(void* data,int type_size,int len)=0;
	virtual void SendSubData(void *data,int type_size,int len,int offset)=0;

	virtual void* MapBuffer(BufferAccess access){return nullptr;}
	virtual bool UnMapBuffer(){return false;}
    };

	DEFINE_SHARED_PTR(IVertexBuffer)
}

#endif
