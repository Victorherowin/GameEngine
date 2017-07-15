//
// Created by moe on 2017-07-15.
//

#ifndef KEDAMA_EXCEPTION_HPP
#define KEDAMA_EXCEPTION_HPP

#include <iostream>
#include <ostream>
#include <sstream>

namespace Exception
{
    class Exception
    {
    public:
        Exception();
		virtual void Message() = 0;
        void PrintStackTrace(std::ostream& o=std::cerr);

    private:
        std::stringstream m_ss;
    };
}

#endif //KEDAMA_EXCEPTION_HPP
