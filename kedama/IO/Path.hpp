//
// Created by moe on 2017-11-07.
//
#ifndef KEDAMA_PATH_HPP
#define KEDAMA_PATH_HPP

#include "../Include.hpp"

namespace Kedama::IO
{
    using namespace std;

    class Path
    {
    public:
        static string Combine(string path1, string path2);
        static string GetDirectoryName(string path);
        static string GetFileName(string path);
    };
}

#endif //KEDAMA_PATH_HPP
