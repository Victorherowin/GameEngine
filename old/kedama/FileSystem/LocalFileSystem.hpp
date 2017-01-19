#ifndef LOCALFILESYSTEM
#define LOCALFILESYSTEM

#include "../Include.hpp"

#include "IFileSystem.hpp"

namespace Kedama {

  class LocalFileSystem:public IFileSystem
  {
  public:

    class LocalFile:public File
    {
    public:
      explicit LocalFile(const string& path);
      void Seek(SeekMode mode,int32_t offset)override;
      void Read(void*data,int32_t size)override;
      void Write(const void *data, int32_t size)override;
      bool Eof()override;
    private:
      fstream m_file;
    };

  public:
    File* Open(const string& path,OpenMode access)override;
    void Close(File *file)override;
  };

}

#endif
