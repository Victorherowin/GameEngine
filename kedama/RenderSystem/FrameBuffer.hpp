#ifndef FRAMEBUFFER
#define FRAMEBUFFER

#include "ITexture2D.hpp"

#include "../Config.hpp"

namespace Kedama
{
  enum class AttachType
  {
    COLOR_ATTACHMENT,
    DEPTH_ATTACHMENT,
    STENCIL_ATTACHMENT,
    DEPTH_STENCIL_ATTACHMENT
  };

  DEFINE_SHARED_PTR(FrameBuffer)

  class FrameBuffer
  {
    public:
    virtual ~FrameBuffer(){}
    virtual void Create(){}
    //virtual void AddTexture1D(ITexture1D* texture,AttachType attachment,int attachment_id=0);
    virtual void AddTexture2D(ITexture2DPtr texture,AttachType attachment,int attachment_id=0,int level=0);
    //virtual void AddTexture3D(ITexture3D* texture,AttachType attachment,int attachment_id=0);

    private:
    vector<ITextureBasePtr> m_texs;
  };
}

#endif
