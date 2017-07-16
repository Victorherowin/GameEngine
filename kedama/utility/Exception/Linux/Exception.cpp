//
// Created by moe on 2017-07-16.
//

#include "Exception.hpp"
#include <backtrace-supported.h>
#include <backtrace.h>
#include <sstream>
#include <cxxabi.h>

namespace Exception
{
    using namespace std;

    const char* Exception::program_file_name=nullptr;
    void Exception::Init(const char* filename)noexcept
    {
        program_file_name=filename;
    }

    const char* Exception::GetFileName()noexcept
    {
        return program_file_name;
    }

    Exception::Exception()noexcept
    {
        stringstream ss;
        backtrace_state* state = backtrace_create_state (program_file_name, BACKTRACE_SUPPORTS_THREADS,
                                                         [](void *data, const char *msg, int errnum) {
                                                             cerr<<msg<<endl; }, nullptr);

        int num = backtrace_full (state, 0, [](void *data, uintptr_t pc, const char *filename, int lineno, const char *function){
            char buf[1024];
            stringstream& ss=*((stringstream*)data);
            size_t length=1024;
            int status=0;
            char* str = __cxxabiv1::__cxa_demangle(function,buf,&length,&status);
            ss<<"StackTrace:"<<endl;
            ss<<"Addrss:0x"<<std::hex<<pc<<"([";
            if(str==nullptr)
                ss<<function;
            else
                ss<<str;
            ss<<"]:("<<filename<<"):"<<std::dec<<lineno;
            ss<<endl;
            return 0;
        }, [](void *data, const char *msg, int errnum){
            cerr<<msg<<endl;
        }, &ss);
        m_stack_trace=std::move(ss.str());
    }

    void Exception::PrintStackTrace(std::ostream& o)noexcept
    {
        o<<m_stack_trace<<std::endl;
    }

    Exception::Exception(const Exception& other)noexcept:Exception()
    {
        m_stack_trace=other.m_stack_trace;
    }

    Exception& Exception::operator=(const Exception& other)noexcept
    {
        m_stack_trace=other.m_stack_trace;
        return *this;
    }

    Exception::Exception(Exception&& other)noexcept:Exception()
    {
        m_stack_trace=std::move(other.m_stack_trace);
    }

    Exception& Exception::operator=(Exception&& other)noexcept
    {
        m_stack_trace=std::move(other.m_stack_trace);
        return *this;
    }
}