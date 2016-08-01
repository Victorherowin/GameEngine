#ifndef GLINDEXBUFFER
#define GLINDEXBUFFER

#include "../IIndexBuffer.hpp"

#include "GL/glew.h"

namespace Kedama {

    class GLIndexBuffer:public IIndexBuffer
    {
	public:
	GLIndexBuffer();
	~GLIndexBuffer();

	void Create(int32_t len)override;

    void SendIndices(vector<uint32_t>& indices)override;
    void SendSubIndices(vector<uint32_t>& indices,int32_t offset,int32_t len)override;

    private:
    GLuint m_ibo;
    };

}

#endif
