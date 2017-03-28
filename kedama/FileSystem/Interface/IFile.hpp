#ifndef _H_IFILE
#define _H_IFILE

#include "../../Include.hpp"
#include "../../Define.hpp"

namespace Kedama
{
  namespace File
  {
    using std::string;
    class KEDAMA_API IFile
    {
    public:

      enum class SeekType
      {
        BEGIN,CURRENT,END
      };

      virtual ~IFile(){}
      virtual bool AvailableWrite()=0;
      virtual const string& GetType()=0;

      virtual bool Eof()=0;
      virtual int Read(void* data,int size)=0;
      virtual int Write(const void* data,int size){throw std::runtime_error("No Implement");}
      virtual void Seek(SeekType type,int offset)=0;
      virtual int Tell()=0;
    };
  }
}

#endif
