/*!
  \file IDeferredRenderer.hpp
  \brief 延迟渲染接口

  \date 2017.01.31
  \author KedamaOvO
*/

#ifndef _H_IDERERREDREDNERER_
#define _H_IDERERREDREDNERER_

#include "../../Include.hpp"
#include "../../GameObject/Camera.hpp"
#include "../../GameObject/Light.hpp"
#include "../CommandBuffer.hpp"

namespace Kedama{
  class IDeferredRenderer
  {
  public:
    virtual ~IDeferredRenderer(){}

    virtual void Render(const RenderCommand& rc)=0;
    virtual void Render(const MergedRenderCommand& mrc)=0;

    virtual void Finish()=0;
  };
}

#endif
