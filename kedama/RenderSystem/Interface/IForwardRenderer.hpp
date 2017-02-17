#ifndef _H_FORWARDRENDERER_
#define _H_FORWARDRENDERER_

#include "../../GameObject/Camera.hpp"
#include "../../GameObject/Light.hpp"
#include "../CommandBuffer.hpp"

namespace Kedama {
  class IForwardRenderer
  {
  public:
    virtual ~IForwardRenderer(){}
    virtual void Render(const RenderCommand& rc)=0;
    virtual void Render(const MergedRenderCommand& mrc)=0;
    virtual void RenderShadow(const RenderCommand& rc)=0;
    virtual void RenderShadow(const MergedRenderCommand& mrc)=0;
  };
}

#endif
