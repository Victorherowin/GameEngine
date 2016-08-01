#ifndef ISHADER
#define ISHADER

#include "../Config.hpp"

namespace Kedama
{
    DEFINE_SHARED_PTR(IShader)

    class IShader
    {
    public:
	virtual ~IShader(){}
    };
}

#endif
