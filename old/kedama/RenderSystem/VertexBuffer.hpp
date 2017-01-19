#ifndef VERTEXBUFFER
#define VERTEXBUFFER

#include <vector>

#include "../Include.hpp"
#include "../Define.hpp"
#include "Vertex.hpp"
#include "BufferEnum.hpp"

namespace Kedama
{
  using namespace std;

  struct VertexLayout
  {
    enum class ValueType
    {
      INT32,INT16,INT8,UINT32,UINT16,UINT8,FLOAT,HALF_FLAOT,
      INT_2_10_10_10,UNSIGNED_INT_2_10_10_10,UNSIGNED_INT_10F_11F_11F
    };

    enum class ValueLength
    {
      FLOAT=1,VEC2,VEC3,VEC4
    };

    struct VertexLayoutInfo
    {
      ValueType type;
      ValueLength size;
      uint32_t stride;
      uint32_t offset;
      bool normalized;
    };

    map<uint16_t,VertexLayoutInfo> layout;
  };

  class VertexBuffer
  {
  public:

    virtual ~VertexBuffer(){}

    //创建一个空VertexBuffer
    virtual void Create(uint32_t vertex_size=4,uint32_t len=0,BufferUsage usage=BufferUsage::Default)=0;

    //发送顶点
    virtual void SendVertices(vector<Vertex>& vertices,BufferUsage usage)=0;
    virtual void SendSubVertices(vector<Vertex>& vertices,uint32_t offset)=0;
    virtual void SendData(void* data,uint32_t len,BufferUsage usage)=0;
    virtual void SendSubData(void *data,uint32_t len,uint32_t offset)=0;

    void SetVertexLayout(const VertexLayout& vl){m_vl=vl;}
    inline const VertexLayout& GetVertexLayout(){return m_vl;}
  private:
    VertexLayout m_vl;
  };
}

#endif
