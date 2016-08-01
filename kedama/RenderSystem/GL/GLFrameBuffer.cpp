#include "GLFrameBuffer.hpp"
#include "GLTexture2D.hpp"

#include <GL/glew.h>

namespace Kedama
{
    GLFrameBuffer::GLFrameBuffer()
    {
        glGenFramebuffers(1,&m_fbo);
    }

    GLFrameBuffer::~GLFrameBuffer()
    {
        glDeleteFramebuffers(1,&m_fbo);
    }

    void GLFrameBuffer::AddTexture2D(ITexture2DPtr texture,AttachType attachment,int32_t attachment_id,int32_t level)
    {
        if(attachment!=AttachType::COLOR_ATTACHMENT&&attachment_id!=0)
        {
            throw runtime_error(string("arguments error"));
        }

        static GLenum __table[4]={GL_COLOR_ATTACHMENT0,GL_DEPTH_ATTACHMENT,GL_STENCIL_ATTACHMENT,GL_DEPTH_STENCIL_ATTACHMENT};

        FrameBuffer::AddTexture2D(texture,attachment,attachment_id,level);
        GLTexture2DPtr tex=std::static_pointer_cast<GLTexture2D>(texture);

        tex->Bind();
        glBindFramebuffer(GL_FRAMEBUFFER,m_fbo);
        glFramebufferTexture2D(GL_FRAMEBUFFER,__table[(int32_t)attachment]+attachment_id,GL_TEXTURE_2D,tex->GetGLObject(),level);
        glBindFramebuffer(GL_FRAMEBUFFER,0);
        tex->Unbind();
    }
}
