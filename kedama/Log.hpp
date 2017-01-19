#ifndef LOG_H
#define LOG_H

#include "utility/Singleton.hpp"
#include "Define.hpp"
#include "Include.hpp"

#define KEDAMALOG(...) Log::GetSingleton().printf(Kedama::LogInfo({__FUNCTION__,__LINE__,__FILE__}),__VA_ARGS__)
#define KEDAMALOGE(...) Log::GetSingleton().eprintf(Kedama::LogInfo({__FUNCTION__,__LINE__,__FILE__}),__VA_ARGS__)

namespace Kedama
{
  using namespace std;

  struct LogInfo
  {
    string function;
    int line;
    string file;
  };

  class KEDAMA_API Log:public Singleton<Log>
  {
  public:
    Log(ostream* os=&std::cout,ostream* error_os=&std::cerr);
    ~Log();
    void SetTarget(ostream* os,ostream* error_os);

    void Print(const LogInfo& info,string str);
    void EPrint(const LogInfo& info,string str);
    int printf(const LogInfo& info,const char* fmt,...);
    int eprintf(const LogInfo& info,const char* fmt,...);

    void SetHook(function<bool(const LogInfo& info,string&)> hook_func);
  private:
    ostream* m_outstream=nullptr;
    ostream* m_errorstream=nullptr;

    function<bool(const LogInfo& info,string&)> m_hook_func;
  };
}

#endif
