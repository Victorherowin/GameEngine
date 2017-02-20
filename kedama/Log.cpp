#include "Log.hpp"

#include <cstdio>
#include <cstdarg>

namespace Kedama
{
  Log::Log(ostream* os,ostream* error_os):m_outstream(os),m_errorstream(error_os)
  {
  }

  Log::~Log()
  {
    if(m_outstream==&std::cout||m_outstream==&std::cerr)return;
    if(m_errorstream==&std::cout||m_errorstream==&std::cerr)return;
    delete m_outstream;
    delete m_errorstream;
  }

  void Log::SetTarget(ostream* os,ostream* error_os)
  {
    if(m_outstream==&std::cout||m_outstream==&std::cerr)return;
    if(m_errorstream==&std::cout||m_errorstream==&std::cerr)return;
    delete m_outstream;
    delete m_errorstream;

    m_outstream=os;
    m_errorstream=error_os;
  }

  void Log::Print(const LogInfo& info,string str)
  {
    if(m_hook_func)
      {
        if(m_hook_func(info,str))
          {
            (*m_outstream)<<str<<std::flush;
          }
      }
    else
      {
        (*m_outstream)<<str<<std::flush;
      }
    m_outstream->flush();
  }

  void Log::EPrint(const LogInfo& info,string str)
  {
    if(m_hook_func)
      {
        if(m_hook_func(info,str))
          {
            (*m_errorstream)<<str<<std::flush;
          }
      }
    else
      {
        (*m_errorstream)<<str<<std::flush;
      }
    m_errorstream->flush();
  }

  int Log::printf(const LogInfo& info,const char* fmt,...)
  {
    va_list va;
    va_start(va,fmt);
    int len=vsnprintf(nullptr,0,fmt,va);
    va_end(va);

    char* tstr=new char[len+1];

    va_start(va,fmt);
    vsnprintf(tstr,len+1,fmt,va);
    va_end(va);

    string str(tstr);

    Print(info,str);
    delete[] tstr;

    return len;
  }

  int Log::eprintf(const LogInfo& info,const char* fmt,...)
  {
    va_list va;
    va_start(va,fmt);
    int len=vsnprintf(nullptr,0,fmt,va);
    va_end(va);

    char* tstr=new char[len+1];

    va_start(va,fmt);
    vsnprintf(tstr,len+1,fmt,va);
    va_end(va);

    string str(tstr);

    EPrint(info,str);

    delete[] tstr;
    return len;
  }

  void Log::SetHook(function<bool(const LogInfo& info,string&)> hook_func)
  {
    m_hook_func=hook_func;
  }
}
