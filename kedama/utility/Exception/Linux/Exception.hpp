//
// Created by moe on 2017-07-16.
//

#ifndef KEDAMA_EXCEPTION_HPP
#define KEDAMA_EXCEPTION_HPP

#include <iostream>

namespace Exception
{
    class Exception
    {
    public:
        Exception()noexcept;
        Exception(const Exception& other)noexcept;
        Exception(Exception&& other)noexcept;
        Exception& operator=(const Exception& other)noexcept;
        Exception& operator=(Exception&& other)noexcept;

        virtual ~Exception()noexcept{}
        virtual const char* Message()const noexcept = 0;
        void PrintStackTrace(std::ostream& o=std::cerr)noexcept;

        static void Init(const char* filename)noexcept;
        static const char* GetFileName()noexcept;

    private:
        std::string m_stack_trace;
        static const char* program_file_name;
    };
}

#endif //KEDAMA_EXCEPTION_HPP
