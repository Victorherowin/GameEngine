#ifndef _DEFINE_H
#define _DEFINE_H

#if defined(_WIN32) && defined(_MSC_VER)
    #ifndef KEDAMA_BUILD
        #define KEDAMA_API __declspec(dllexport)
    #else
        #define KEDAMA_API __declspec(dllimport)
    #endif
#else
    #define KEDAMA_API
#endif

#include <memory>

#define DEFINE_SHARED_PTR(type) class type;typedef std::shared_ptr<type> type##Ptr;
#define DEFINE_UNIQUE_PTR(type) class type;typedef std::unique_ptr<type> type##Ptr;

#define DEFINE_SHARED_CREATE_FUNC(type,...) inline static std::shared_ptr<type> Create##type(__VA_ARGS__)\
    {\
        return std::shared_ptr<type>(__VA_ARGS__);\
    }
	
#define DEFINE_UNIQUE_CREATE_FUNC(type,...) inline static std::unique_ptr<type> Create##type(__VA_ARGS__)\
    {\
        return std::unique_ptr<type>(new type(__VA_ARGS__));\
    }


#endif
