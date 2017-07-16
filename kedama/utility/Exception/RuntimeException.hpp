//
// Created by moe on 2017-07-16.
//

#ifndef KEDAMA_RUNTIMEEXCEPTION_HPP
#define KEDAMA_RUNTIMEEXCEPTION_HPP

#include "ExceptionCommon.hpp"

namespace Exception
{
    class RuntimeException:Exception
    {
    public:
        explicit RuntimeException(const std::string& what)noexcept;
        explicit RuntimeException(const char* what)noexcept;

        RuntimeException(const RuntimeException& other);
        RuntimeException(RuntimeException&& other);
        RuntimeException& operator=(const RuntimeException& other);
        RuntimeException& operator=(RuntimeException&& other);

        virtual const char* Messgae()const noexcept ;
    };
}

#endif //KEDAMA_RUNTIMEEXCEPTION_HPP
