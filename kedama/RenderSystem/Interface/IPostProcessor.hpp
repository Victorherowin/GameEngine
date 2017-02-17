/*!
  \file IPostProceesor.hpp
  \brief 后处理接口
  bind point:
    15 color
    16 gPostition+gDepth
    17 gNormal

  \author KedamaOvO
  \date 2017.02.08
*/

#ifndef _H_IPOSTPROCESSOR
#define _H_IPOSTPROCESSOR

#include "../RenderCommand.hpp"

namespace Kedama {
  class IPostProcessor
  {
  public:
    virtual ~IPostProcessor(){}
    virtual void PostProcess(const PostProcessCommand& ppc)=0;
  };
}

#endif
