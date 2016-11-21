#ifndef IRENDERBUFFER
#define IRENDERBUFFER

#include "../Include.hpp"
#include "../Define.hpp"

namespace Kedama {
  DEFINE_SHARED_PTR(IRenderBuffer)

  class IRenderBuffer
  {
  public:
    virtual ~IRenderBuffer(){}
  };
}

#endif
