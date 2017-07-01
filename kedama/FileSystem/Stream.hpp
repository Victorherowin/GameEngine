#ifndef _H_Stream
#define _H_Stream

#include "../Include.hpp"
#include "../Define.hpp"

namespace Kedama
{
    namespace File
    {
        using std::string;

        enum class SeekMode
        {
            Begin, Current, End
        };

        class KEDAMA_API Stream
        {
        public:

            virtual ~Stream() {}

            virtual const string& GetType()=0;
            virtual bool Eof()=0;
            virtual bool IsBad()=0;
            virtual int Read(void* data, int size)=0;
            virtual int Tell()=0;
            virtual void Close()=0;
            virtual int Write(const void* data, int size);
            virtual void Seek(SeekMode type, int offset);
        };
    }
}

#endif
