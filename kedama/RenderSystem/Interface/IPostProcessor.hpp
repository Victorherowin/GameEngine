/*!
  \file IPostProceesor.hpp
  \brief 后处理接口
  0 color
  1 gPostition+gDepth
  2 gNormal

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
