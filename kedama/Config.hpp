#ifndef _H_CONFIG
#define _H_CONFIG

#if defined(_WIN32) && defined(_MSC_VER)
    #ifndef KEDAMA_BUILD
        #define KEDAMA_API __declspec(dllexport)
    #else
        #define KEDAMA_API __declspec(dllimport)
    #endif
#else
    #define KEDAMA_API
#endif

#define DEFINE_SHARED_PTR(type) class type;typedef std::shared_ptr<type> type##Ptr;

#define GLM_FORCE_RADIANS

#include <GL/glew.h>

#include <cstdint>

#include <string>
#include <map>
#include <vector>
#include <list>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <memory>
#include <functional>
#include <type_traits>

#include <glm/integer.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/type_precision.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>



namespace Kedama
{
    using std::string;
    using std::map;
    using std::vector;
    using std::list;
    using std::pair;
    using std::runtime_error;
    using std::fstream;
    using std::ostream;
    using std::function;
    //class File;
}

#endif
