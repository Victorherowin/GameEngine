#ifndef IFILESYSTEM
#define IFILESYSTEM

#include "../Include.hpp"

namespace Kedama {
  using namespace std;

  class IFileSystem
  {
  public:
    enum class SeekMode
    {
      Begin,Current,End
    };

    enum class OpenMode
    {
      ReadOnly,WriteOnly,ReadAndWrite,Append,Binary
    };

    class File
    {
    public:
      virtual ~File(){}
      virtual bool Eof()=0;
      virtual void Seek(SeekMode mode,int offset)=0;
      virtual void Read(void* data,int size)=0;
      virtual void Write(const void* data,int size);

    protected:
      IFileSystem* m_file_system=nullptr;
    };

  public:
    virtual ~IFileSystem(){}
    virtual File* Open(const string& path,OpenMode access)=0;
    virtual void Close(File* file)=0;
  };

}

#endif
