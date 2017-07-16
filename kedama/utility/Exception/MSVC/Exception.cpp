//
// Created by moe on 2017-07-15.
//

#include <sstream>

#include "Exception.hpp"
#include <windows.h>
#include <Dbghelp.h>
#pragma comment( lib, "dbghelp.lib" )

#define TRACE_DEPTH 1024

namespace Exception
{
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
        const ULONG framesToSkip = 0;
        const ULONG framesToCapture = TRACE_DEPTH;
        void* backTrace[framesToCapture]{};
        ULONG backTraceHash = 0;

        std::stringstream ss;
        ss << "StackTrace:" << std::endl;
        int num = CaptureStackBackTrace(0, framesToCapture, backTrace, nullptr);
        byte _symbol[sizeof(SYMBOL_INFO) + 1024]{};
        SYMBOL_INFO* symbol = (SYMBOL_INFO*) &_symbol;
        symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
        symbol->MaxNameLen = 1024;

        HANDLE hProcess = GetCurrentProcess();
        SymInitialize(hProcess, NULL, TRUE);
        for (int i = 0; i < num; ++i) {
            DWORD64  sym_dwDisplacement = 0;
			if (SymFromAddr(hProcess, (DWORD64)backTrace[i], &sym_dwDisplacement, symbol))
			{
				char* str=nullptr;
				ss << "Address:0x" << std::hex << symbol->Address << "([" << str<<"]";
				IMAGEHLP_LINE64 line64;
				line64.SizeOfStruct = sizeof(IMAGEHLP_LINE64);
				DWORD line_dwDisplacement = 0;
				if (SymGetLineFromAddr64(hProcess, (DWORD64)backTrace[i], &line_dwDisplacement, &line64))
				{
					ss << std::dec << ":[" << line64.FileName << "]:" << line64.LineNumber;
				}
				else
				{
					ss << "+0x" << sym_dwDisplacement;
				}
				ss << ")" << std::endl;
			} 
			else 
			{
				ss << "Address:0x"<< std::hex <<(DWORD64)backTrace[i]<<"(???)" << std::endl;
			}
        }
        SymCleanup(hProcess);
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