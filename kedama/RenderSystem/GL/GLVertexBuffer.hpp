#ifndef GLVERTEXBUFFER
#define GLVERTEXBUFFER

#include "../VertexBuffer.hpp"

#include "GL/glew.h"

namespace Kedama
{
  DEFINE_SHARED_PTR(GLVertexBuffer)

  struct GLVertex
  {
    float m_position[3];
    int16 m_normal[3];
    uint16 m_uv[2];
    int16 m_tbn_quat[4];

    uint16 m_bone_index[4];
    uint8 m_weight[4];
  };

  class GLVertexBuffer:public VertexBuffer
  {
  public:
  GLVertexBuffer();
  ~GLVertexBuffer();

  void Bind();
  void Unbind();

  void Create(int32_t vertex_size,int32_t len,BufferUsage usage)override;
  void SendVertices(vector<Vertex>& vertices,BufferUsage usage)override;
  void SendSubVertices(vector<Vertex>& vertices,int32_t offset)override;
  void SendData(void* data,int32_t len,BufferUsage usage)override;
  void SendSubData(void *data,int32_t len,int32_t offset)override;

  inline GLuint GetObj(){m_vbo;}
  private:
  GLuint m_vbo;
  GLenum m_usage;

  void* m_maped_ptr=nullptr;
};
}

#endif
