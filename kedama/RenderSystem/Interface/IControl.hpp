/*!
  \file IControl.hpp
  \brief 渲染控制器

  \author KedamaOvO
  \date 2017.02.06

*/
#ifndef _H_ICONTROL
#define _H_ICONTROL

#include "../../Include.hpp"
#include "../RenderSystemClass.hpp"
#include "../../GameObject/Light.hpp"
#include "../../GameObject/Camera.hpp"

namespace Kedama {
  enum ClearBufferBit
  {
    COLOR_BUFFER=1,DEPTH_BUFFER=2,ACCUM_BUFFER=4,STENCIL_BUFFER=8
  };

  class IControl
  {
  public:
    virtual ~IControl(){}

    virtual void SetLights(vector<Light*>& lights)=0;
    virtual void SetCamera(Camera* camera)=0;
    virtual void ClearColor(glm::vec4 color)=0;
    virtual void ClearDepth(float depth)=0;
    virtual void ClearStencil(int32_t s)=0;
    virtual void ClearAccum(glm::vec4 accum)=0;
    virtual void Clear(int32_t clear_bit)=0;
    virtual void Present()=0;
    virtual IWindow* GetWindow()=0;
    virtual IForwardRenderer* GetForwardRenderer()=0;
    virtual IDeferredRenderer* GetDeferredRenderer()=0;
    virtual IPostProcessor* GetPostProcessor()=0;
  };
}

#endif
