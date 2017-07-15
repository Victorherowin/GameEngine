//
// Created by moe on 2017-07-16.
//

#ifndef KEDAMA_EXCEPTIONCOMMON_HPP
#define KEDAMA_EXCEPTIONCOMMON_HPP

#ifdef _MSC_VER
    #include "MSVC/Exception.hpp"
#else
    #include "Linux/Exception.hpp"
#endif

#endif //KEDAMA_EXCEPTIONCOMMON_HPP
