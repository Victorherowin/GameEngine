#ifndef _H_Stream
#define _H_Stream

#include "../Include.hpp"
#include "../Define.hpp"

namespace Kedama::File 
{
    using IStream = std::istream;
	using OStream = std::ostream;
	using IOStream = std::iostream;
	using StreamBuffer = std::streambuf;
}

#endif
