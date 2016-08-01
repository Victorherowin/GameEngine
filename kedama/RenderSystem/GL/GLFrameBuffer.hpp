#ifndef GLFRAMEBUFFER
#define GLFRAMEBUFFER

#include "GLTextureBase.hpp"

#include "../FrameBuffer.hpp"

#include "../../Config.hpp"

namespace Kedama
{
    class GLFrameBuffer:public FrameBuffer
	{
	public:
		GLFrameBuffer();
		~GLFrameBuffer();

         void AddTexture2D(ITexture2DPtr texture,AttachType attachment,int32_t attachment_id=0,int32_t level=0)override;
	private:
        GLuint m_fbo;
		vector<GLTextureBase*> m_texs;
	};
}

#endif
