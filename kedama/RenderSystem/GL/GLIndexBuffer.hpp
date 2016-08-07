#ifndef GLINDEXBUFFER
#define GLINDEXBUFFER

#include "../IIndexBuffer.hpp"

#include "GL/glew.h"

namespace Kedama{

  DEFINE_SHARED_PTR(GLIndexBuffer)

  class GLIndexBuffer:public IIndexBuffer
  {
  public:
  GLIndexBuffer();
  ~GLIndexBuffer();

  void Bind();
  void Unbind();

  void Create(int32_t len)override;

  void SendIndices(vector<uint32_t>& indices)override;
  void SendSubIndices(vector<uint32_t>& indices,int32_t offset,int32_t len)override;

  inline uint32_t GetSize(){return m_size;}

  inline GLuint GetObj(){return m_ibo;}

  private:
  GLuint m_ibo;
  uint32_t m_size;
};

}

#endif
