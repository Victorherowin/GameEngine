//
// Created by moe on 2017-07-15.
//

#ifndef KEDAMA_EXCEPTION_HPP
#define KEDAMA_EXCEPTION_HPP

#include <sstream>
#include <iostream>

namespace Exception
{
    class Exception
    {
    private:
        Exception()noexcept;
        Exception(const Exception& other)noexcept;
        Exception(Exception&& other)noexcept;
        Exception& operator=(const Exception& other)noexcept;
        Exception& operator=(Exception&& other)noexcept;

        virtual ~Exception()noexcept{}
		virtual const char* Message()const noexcept = 0;
        void PrintStackTrace(std::ostream& o=std::cerr)noexcept;

    private:
        std::string m_stack_trace;
    };
}

#endif //KEDAMA_EXCEPTION_HPP
