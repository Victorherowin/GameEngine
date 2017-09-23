#ifndef _H_Stream
#define _H_Stream

#include "../Include.hpp"
#include "../Define.hpp"

namespace Kedama::IO
{
    enum class StreamSeek
    {
        Current,Begin,End
    };

    class IStream
    {
    public:
        virtual ~IStream()= default;

        virtual bool CanWrite()=0;
        virtual bool CanRead()=0;
        virtual bool CanSeek()=0;
        virtual bool Eof()=0;
        virtual void Close()=0;


        virtual void Read(uint8_t* data,size_t length)=0;
        virtual void Write(const uint8_t* data,size_t length)=0;
        virtual void Seek(StreamSeek type,size_t offset)=0;
    };
}

#endif
