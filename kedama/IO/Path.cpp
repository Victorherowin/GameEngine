//
// Created by moe on 2017-11-07.
//

#include "Path.hpp"

namespace Kedama::IO
{
    string Path::Combine(string path1,string path2)
    {
        auto it =path1.end()-1;
        if(*it=='/')
            path1.pop_back();

        it=path2.begin();
        if(*it!='/')
            path2.insert(it,'/');
        return path1+path2;
    }

    string Path::GetDirectoryName(string path)
    {
        auto pos = path.rfind('/');
        return path.substr(0,pos);
    }

    string Path::GetFileName(string path)
    {
        auto pos = path.rfind('/');
        return path.substr(pos+1);
    }
}