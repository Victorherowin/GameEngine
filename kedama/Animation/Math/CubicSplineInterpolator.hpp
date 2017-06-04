//资料:http://www.cnblogs.com/xpvincent/archive/2013/01/26/2878092.html

#ifndef _H_CUBIC_SPLINE_INTERPOLATOR
#define _H_CUBIC_SPLINE_INTERPOLATOR

#include "IInterpolator.hpp"
#include "../../Include.hpp"
#include "../../GLMInclude.hpp"

namespace Kedama {
  namespace Internation {
    using namespace std;
    using namespace glm;

    class CubicSplineInterpolator:public IInterpolator
    {
    public:
      CubicSplineInterpolator();
      ~CubicSplineInterpolator();
      void AddPoint(const vec2& p);
      float Interpolate(float t)override final;
    private:
      void Calculate();
    private:
      vector<vec2> m_points;
    };
  }
}

#endif
