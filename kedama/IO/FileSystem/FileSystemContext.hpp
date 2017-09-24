//
// Created by moe on 2017-09-21.
//

#ifndef KEDAMA_FILESYSTEMCONTEXT_HPP
#define KEDAMA_FILESYSTEMCONTEXT_HPP

#include "../../Include.hpp"
#include "IFileSystem.hpp"

namespace Kedama::FileSystem
{
    using namespace std;

    class FileSystemContext
    {
    public:
        ~FileSystemContext();

        IStream* OpenRead(const string& file);
        IStream* OpenWrite(const string& file);
        IStream* Open(const string& file);

        void Map(string path,IFileSystem* fs);
        void Unmap(string path);
        bool FileExist(const string& file);
        bool DirectorExist(const string& path);

        static string Combine(string path1,string path2);
        static string GetDirectoryName(string path);
        static string GetFileName(string path);
    private:
        IFileSystem* FindMappedFileSystem(const string& file,string* out_path);
        string GetBestMatchPath(string path);
    private:
        map<string,IFileSystem*> m_mapped_fs;
    };
}

#endif //KEDAMA_FILESYSTEMCONTEXT_HPP
