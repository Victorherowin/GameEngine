//
// Created by moe on 2017-07-15.
//

#include <sstream>

#include "Exception.hpp"

#include <signal.h>
#include <windows.h>
#include <Dbghelp.h>

#ifdef __MINGW_GCC_VERSION
#include <cxxabi.h>
#include <backtrace-supported.h>
#include <backtrace.h>
#endif

namespace Exception
{
	using namespace std;

    static void BackTrace(std::ostream& o,const char* filename,int skip, CONTEXT* context =nullptr)
    {
        o << "StackTrace:" << std::endl;
        byte _symbol[sizeof(SYMBOL_INFO) + 1024]{};
        SYMBOL_INFO* symbol = (SYMBOL_INFO*) &_symbol;
        symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
        symbol->MaxNameLen = 1024;

        HANDLE hProcess = GetCurrentProcess();
        SymInitialize(hProcess, NULL, TRUE);
		CONTEXT context_record;

		if(context==nullptr)
		{
			RtlCaptureContext( &context_record );
		}else{
			context_record=*context;
		}
		// Initialize stack walking.
		STACKFRAME64 stack_frame;
		memset(&stack_frame, 0, sizeof(stack_frame));
#if defined(_WIN64)
		int machine_type = IMAGE_FILE_MACHINE_AMD64;
		stack_frame.AddrPC.Offset = context_record.Rip;
		stack_frame.AddrFrame.Offset = context_record.Rbp;
		stack_frame.AddrStack.Offset = context_record.Rsp;
#else
		int machine_type = IMAGE_FILE_MACHINE_I386;
		stack_frame.AddrPC.Offset = context_record.Eip;
		stack_frame.AddrFrame.Offset = context_record.Ebp;
		stack_frame.AddrStack.Offset = context_record.Esp;
#endif
		stack_frame.AddrPC.Mode = AddrModeFlat;
		stack_frame.AddrFrame.Mode = AddrModeFlat;
		stack_frame.AddrStack.Mode = AddrModeFlat;

		while (StackWalk64(machine_type,
			GetCurrentProcess(),
			GetCurrentThread(),
			&stack_frame,
			&context_record,
			NULL,
			&SymFunctionTableAccess64,
			&SymGetModuleBase64,
			NULL))
		{
			DWORD64  sym_dwDisplacement = 0;
			if (SymFromAddr(hProcess, (DWORD64)stack_frame.AddrPC.Offset, &sym_dwDisplacement, symbol))
			{
				o << "Address:0x" << std::hex << symbol->Address << "([" << symbol->Name << "]";
				IMAGEHLP_LINE64 line64;
				line64.SizeOfStruct = sizeof(IMAGEHLP_LINE64);
				DWORD line_dwDisplacement = 0;
				if (SymGetLineFromAddr64(hProcess, (DWORD64)stack_frame.AddrPC.Offset, &line_dwDisplacement, &line64))
				{
					o << std::dec << ":[" << line64.FileName << "]:" << line64.LineNumber;
				}
				else
				{
					o << "+0x" << sym_dwDisplacement;
				}
				o << ")" << std::endl;
			}
			else
			{
#ifdef __MINGW_GCC_VERSION
				backtrace_state* state = backtrace_create_state (filename, BACKTRACE_SUPPORTS_THREADS,
																 [](void *data, const char *msg, int errnum) {
																	 cerr<<msg<<endl; }, nullptr);
				void* pair[]={&o,(void*)stack_frame.AddrPC.Offset};
				backtrace_pcinfo(state,stack_frame.AddrPC.Offset,[](void *data, uintptr_t pc, const char *filename, int lineno, const char *function){
					void** pair=(void**)data;
					ostream& o=*((ostream*)pair[0]);

					char buf[1024];
					size_t length=1024;
					int status=0;
					char* str = __cxxabiv1::__cxa_demangle(function,buf,&length,&status);
					o<<"Addrss:0x"<<std::hex<<pc<<"([";
					if(str==nullptr)
						o<<function;
					else
						o<<str;
					o<<"]:("<<filename<<"):"<<std::dec<<lineno;
					o<<endl;
					return 0;
				}, [](void *data, const char *msg, int errnum){
					void** pair=(void**)data;
					ostream& o=*((ostream*)pair[0]);
					o << "Address:0x" << std::hex << (DWORD64)pair[1] << "(???)" << std::endl;
				}, pair);
				free(state);
#else
				o << "Address:0x" << std::hex << (DWORD64)stack_frame.AddrPC.Offset << "(???)" << std::endl;
#endif
			}
		}
        SymCleanup(hProcess);
    }

	static std::ostream* po;
	const char* Exception::program_file_name=nullptr;
	LONG WINAPI TopLevelExceptionHandler(PEXCEPTION_POINTERS pExceptionInfo)
	{
		BackTrace(*po, Exception::GetFileName(), 2,pExceptionInfo->ContextRecord);
		return EXCEPTION_CONTINUE_SEARCH;
	}

    void Exception::Init(const char* filename,std::ostream& o)noexcept
    {
		po = &o;
        program_file_name=filename;
		SetUnhandledExceptionFilter(TopLevelExceptionHandler);
    }

    const char* Exception::GetFileName()noexcept
    {
        return program_file_name;
    }

    Exception::Exception()noexcept
    {
        std::stringstream ss;
        BackTrace(ss,program_file_name,0);
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

    const char* Exception::Message() const noexcept
    {
        return "Execption";
    }

}