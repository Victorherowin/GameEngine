#ifndef LOG_H
#define LOG_H

#include "utility/Singleton.hpp"
#include "Define.hpp"
#include "Include.hpp"

#define KEDAMALOG(fmt,...) Logger::GetSingleton().printf(Kedama::LogInfo({__FUNCTION__,__LINE__,__FILE__}),fmt,##__VA_ARGS__)
#define KEDAMALOGE(fmt,...) Logger::GetSingleton().eprintf(Kedama::LogInfo({__FUNCTION__,__LINE__,__FILE__}),fmt,##__VA_ARGS__)

namespace Kedama
{
  using namespace std;

  struct LogInfo
  {
    string function;
    int line;
    string file;
  };

  class KEDAMA_API Logger:public Singleton<Logger>
  {
  public:
	  
	  using LoggerHookFunction = function<bool(const LogInfo& info, string&)>;

	  enum class Level
	  {
		  Info,Warning,Error, Fatal
	  };

    Logger(ostream* os=&std::cout,ostream* error_os=&std::cerr);
    ~Logger();
    void SetTarget(ostream* os,ostream* error_os);

    void Print(const LogInfo& info,string str);
    void EPrint(const LogInfo& info,string str);
    int printf(const LogInfo& info,const char* fmt,...);
    int eprintf(const LogInfo& info,const char* fmt,...);

    void SetHook(function<bool(const LogInfo& info,string&)> hook_func);
  private:
    ostream* m_outstream=nullptr;
    ostream* m_errorstream=nullptr;

	LoggerHookFunction m_hook_func;
  };
}

#endif
