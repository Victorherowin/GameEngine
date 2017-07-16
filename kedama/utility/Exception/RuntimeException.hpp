//
// Created by moe on 2017-07-16.
//

#ifndef KEDAMA_RUNTIMEEXCEPTION_HPP
#define KEDAMA_RUNTIMEEXCEPTION_HPP

#include "ExceptionCommon.hpp"

namespace Exception
{
    class RuntimeException:public Exception
    {
    public:
        explicit RuntimeException(const std::string& what="")noexcept;
        explicit RuntimeException(const char* what="")noexcept;

        RuntimeException(const RuntimeException& other)noexcept;
        RuntimeException(RuntimeException&& other)noexcept;
        RuntimeException& operator=(const RuntimeException& other)noexcept;
        RuntimeException& operator=(RuntimeException&& other)noexcept;

        virtual const char* Message()const noexcept override;

    private:
        std::string m_what;
    };
}

#endif //KEDAMA_RUNTIMEEXCEPTION_HPP
