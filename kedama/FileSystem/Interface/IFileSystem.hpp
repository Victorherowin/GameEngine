#ifndef _H_IFILESYSTEM
#define _H_IFILESYSTEM

#include "../../Define.hpp"

#include "IFile.hpp"
#include <string>

namespace Kedama
{
  namespace File
  {
    using namespace std;

    enum AccessFlag
    {
      Read=1,Write=2,Create=4
    };

    class KEDAMA_API IFileSystem
    {
    public:
      virtual ~IFileSystem(){}

      virtual IFile* Open(const string& file,AccessFlag flag)=0;
      virtual bool Opening(IFile* fp)=0;
      virtual void Close(IFile* file)=0;
      virtual const string& GetFileType()=0;
    };
  }
}

#endif
