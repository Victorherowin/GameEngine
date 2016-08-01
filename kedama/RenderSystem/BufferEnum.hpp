#ifndef BUFFER
#define BUFFER

namespace Kedama
{
    enum class BufferUsage
    {
	Default,StaticDraw,DynamicDraw
    };

    enum class BufferAccess
    {
	RO,WO,RW
    };
}

#endif
