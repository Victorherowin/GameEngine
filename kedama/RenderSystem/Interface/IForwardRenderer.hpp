#ifndef _H_FORWARDRENDERER_
#define _H_FORWARDRENDERER_

#include "../../GameObject/Camera.hpp"
#include "../CommandBuffer.hpp"

namespace Kedama {
  class IForwardRenderer
  {
  public:
    virtual ~IForwardRenderer(){}
    virtual void Render(const RenderCommand& cb)=0;
    virtual void Render(const MergedRenderCommand& mrc)=0;

    virtual void SetCamera(Camera* camera)=0;
  };
}

#endif
