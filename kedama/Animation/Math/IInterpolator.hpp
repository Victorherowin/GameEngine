#ifndef _H_IINTERPOLATOR
#define _H_IINTERPOLATOR

namespace Kedama {
  namespace Internation {
    class IInterpolator
    {
    public:
      virtual ~IInterpolator()=default;
      ///t:0~1
      virtual float Interpolate(float t)=0;
    };
  }
}

#endif
