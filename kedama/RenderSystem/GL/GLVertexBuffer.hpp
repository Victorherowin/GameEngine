#ifndef GLVERTEXBUFFER
#define GLVERTEXBUFFER

#include "../IVertexBuffer.hpp"

#include "GL/glew.h"

namespace Kedama
{
  class GLVertexBuffer:public IVertexBuffer
  {
  public:
    GLVertexBuffer();
    ~GLVertexBuffer();

    void Create(int32_t vertex_size,int32_t len,BufferUsage usage)override;
    void SendVertices(vector<Vertex>& vertices)override;
    void SendSubVertices(vector<Vertex>& vertices,int32_t offset)override;
    void SendData(void* data,int32_t type_size,int32_t len)override;
    void SendSubData(void *data,int32_t type_size,int32_t len,int32_t offset)override;

    void* MapBuffer(BufferAccess access)override;
    bool UnMapBuffer()override;
  private:
    GLuint m_vbo;
    GLenum m_usage;
  };
}

#endif
