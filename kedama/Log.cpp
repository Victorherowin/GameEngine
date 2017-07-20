#include "Log.hpp"

#include "Include.hpp"

#include <cstdio>
#include <cstdarg>
#include <ctime>

namespace Kedama
{
	Logger::Logger(ostream* os,ostream* error_os):m_outstream(os),m_errorstream(error_os)
  {
  }

  Logger::~Logger()
  {
    if(m_outstream==&std::cout||m_outstream==&std::cerr)return;
    if(m_errorstream==&std::cout||m_errorstream==&std::cerr)return;
    delete m_outstream;
    delete m_errorstream;
  }

  void Logger::SetTarget(ostream* os,ostream* error_os)
  {
    if(m_outstream==&std::cout||m_outstream==&std::cerr)return;
    if(m_errorstream==&std::cout||m_errorstream==&std::cerr)return;
    delete m_outstream;
    delete m_errorstream;

    m_outstream=os;
    m_errorstream=error_os;
  }

  void Logger::Print(const LogInfo& info,string str)
  {
    char buf[128];
    time_t timer;
    time(&timer);
    struct tm* t = localtime(&timer);

    strftime(buf,128,"[%H:%M:%S]",t);
    (*m_outstream)<<"[thread:"<<std::this_thread::get_id()<<"]"<<std::flush;
    (*m_outstream)<<buf<<std::flush;

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
  }

  void Logger::EPrint(const LogInfo& info,string str)
  {
    char buf[128];
    time_t timer;
    time(&timer);
    struct tm* t = localtime(&timer);

    strftime(buf,128,"[%H:%M:%S]",t);
    (*m_errorstream)<<"[thread:"<<std::this_thread::get_id()<<"]"<<std::flush;
    (*m_errorstream)<<buf<<std::flush;

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
  }

  int Logger::printf(const LogInfo& info,const char* fmt,...)
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

  int Logger::eprintf(const LogInfo& info,const char* fmt,...)
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

  void Logger::SetHook(function<bool(const LogInfo& info,string&)> hook_func)
  {
    m_hook_func=hook_func;
  }
}
