//
// Created by moe on 2017-07-15.
//

#include "Exception.hpp"
#include <windows.h>
#include <Dbghelp.h>
#pragma comment( lib, "dbghelp.lib" )

#define TRACE_DEPTH 1024

namespace Exception
{
    Exception::Exception()
    {
        const ULONG framesToSkip = 0;
        const ULONG framesToCapture = TRACE_DEPTH;
        void* backTrace[framesToCapture]{};
        ULONG backTraceHash = 0;

        m_ss << "StackTrace:" << std::endl;
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
				m_ss << "Address:0x" << std::hex << symbol->Address << "([" << str<<"]";
				IMAGEHLP_LINE64 line64;
				line64.SizeOfStruct = sizeof(IMAGEHLP_LINE64);
				DWORD line_dwDisplacement = 0;
				if (SymGetLineFromAddr64(hProcess, (DWORD64)backTrace[i], &line_dwDisplacement, &line64))
				{
					m_ss << std::dec << ":[" << line64.FileName << "]:" << line64.LineNumber;
				}
				else
				{
					m_ss << "+0x" << sym_dwDisplacement;
				}
				m_ss << ")" << std::endl;
			} 
			else 
			{
				m_ss << "Address:0x"<< std::hex <<(DWORD64)backTrace[i]<<"(???)" << std::endl;
			}
        }
        SymCleanup(hProcess);
    }

    void Exception::PrintStackTrace(std::ostream& o)
    {
        auto str=std::move(m_ss.str());
        o<<str<<std::endl;
    }
}