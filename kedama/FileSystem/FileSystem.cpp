//
// Created by moe on 2017-07-01.
//
#include "FileSystem.hpp"

namespace Kedama
{
    namespace File
    {
        void FileSystem::Mount(const string& path, FileSystem* fs)
        {
            throw std::runtime_error("No Implement");
        }

        void FileSystem::Unmount(const string& path)
        {
            throw std::runtime_error("No Implement");
        }
    }
}
