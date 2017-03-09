#include "LocalFile.hpp"

#ifdef _WIN32
#define SLASH "\\"
#else
#define SLASH "/"
#endif

namespace Kedama
{
  namespace File
  {
    LocalFile::LocalFile(const string& file,AccessFlag flag)
    {
      string access_flag;
      if(flag&AccessFlag::Create)
        access_flag="w";
      if(flag&AccessFlag::Read)
        access_flag+="r";
      if(flag&AccessFlag::Write)
        access_flag+="a";
      m_fp=fopen(file.c_str(),access_flag.c_str());
      fseek(m_fp,0,SEEK_SET);
      int pos=file.rfind(SLASH);
      if(pos!=string::npos)
        m_name=file.substr(pos+1);
      else
        m_name=file;
    }

    LocalFile::~LocalFile()
    {
      fclose(m_fp);
    }

    bool LocalFile::AvailableWrite()
    {
      return true;
    }

    const string& LocalFile::GetType()
    {
      static string str("LocalFile");
      return str;
    }

    bool LocalFile::Eof()
    {
      return feof(m_fp);
    }

    int LocalFile::Read(void* data,int size)
    {
      return fread(data,1,size,m_fp);
    }

    int LocalFile::Write(const void* data,int size)
    {
      return fwrite(data,1,size,m_fp);
    }

    void LocalFile::Seek(SeekType type,int offset)
    {
      fseek(m_fp,offset,(int)type);
    }

    int LocalFile::Tell()
    {
      return ftell(m_fp);
    }
  }
}
