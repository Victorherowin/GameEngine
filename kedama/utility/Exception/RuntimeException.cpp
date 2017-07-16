//
// Created by moe on 2017-07-16.
//

#include "RuntimeException.hpp"

namespace Exception
{
    RuntimeException::RuntimeException(const std::string& what)noexcept : Exception(),m_what(what) {}

    RuntimeException::RuntimeException(const char* what)noexcept : Exception(),m_what(what) {}

    RuntimeException::RuntimeException(const RuntimeException& other)noexcept
    {
        m_what=other.m_what;
    }

    RuntimeException::RuntimeException(RuntimeException&& other)noexcept
    {
        m_what=std::move(other.m_what);
    }

    RuntimeException& RuntimeException::operator=(const RuntimeException& other)noexcept
    {
        m_what=other.m_what;
        return *this;
    }

    RuntimeException& RuntimeException::operator=(RuntimeException&& other)noexcept
    {
        m_what=std::move(other.m_what);
        return *this;
    }

    const char* RuntimeException::Message() const noexcept
    {
        return m_what.c_str();
    }


}