#include "../../Config.hpp"
#include <limits>

namespace Kedama
{
    namespace detail
    {
        using namespace glm;

        template <typename T,typename P>
        inline void FloatTo(T n,P* target)
        {
            static_assert(std::is_same<T,vec1>::value ||
                          std::is_same<T,vec2>::value||
                          std::is_same<T,vec3>::value||
                          std::is_same<T,vec4>::value||
                          std::is_same<T,quat>::value,"Bad Type");

            static_assert(std::is_integral<P>::value,"Bad Number Type");
            for(int i=0;i<n.length();++i)
            {
                target[i]=n[i]*std::numeric_limits<P>::max();
            }
        }

        template<typename P>
        inline P FloatTo(float n)
        {
            static_assert(std::is_integral<P>::value,"Bad Number Type");
            return n*std::numeric_limits<P>::max();
        }
    }
}
