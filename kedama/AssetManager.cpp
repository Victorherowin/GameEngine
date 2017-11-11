#include "AssetManager.hpp"

#include <sys/stat.h>

namespace Kedama
{
    void AssetManager::Map(std::string path, Kedama::FileSystem::IFileSystem* fs)
    {
        if(*(path.end()-1)=='/')
            path.pop_back();

        auto it = m_mapped_fs.find(path);
        if(it!=m_mapped_fs.end())
            throw Exception::RuntimeException("Path Exist!");
        m_mapped_fs[path] = fs;
    }

    bool AssetManager::DirectorExist(const std::string& path)
    {
#ifdef _WIN32
        struct _stat file_stat;
        if ((_stat(path.c_str(), &file_stat) == 0) && (file_stat.st_mode & _S_IFDIR)) {
            return true;
        }
#else
        struct stat file_stat;
            if ((stat(path.c_str(), &file_stat) == 0) && S_ISDIR(file_stat.st_mode))
            {
                return true;
            }
#endif
        return false;
    }

    bool AssetManager::FileExist(const string& file)
    {
        FILE* fp = fopen(file.c_str(), "e");
        if (fp == nullptr)
            return false;
        fclose(fp);
        return true;
    }

    void AssetManager::Unmap(string path)
    {
        auto it = m_mapped_fs.find(path);
        if(it==m_mapped_fs.end())return;
        m_mapped_fs.erase(it);
    }

    IStream* AssetManager::OpenRead(const string& file)
    {
        string mapped_path;
        IFileSystem* fs = FindMappedFileSystem(file,&mapped_path);
        return fs->OpenRead(mapped_path);
    }

    IStream* AssetManager::OpenWrite(const string& file)
    {
        string mapped_path;
        IFileSystem* fs = FindMappedFileSystem(file,&mapped_path);
        return fs->OpenWrite(mapped_path);
    }

    IStream* AssetManager::Open(const string& file)
    {
        string mapped_path;
        IFileSystem* fs = FindMappedFileSystem(file,&mapped_path);
        return fs->Open(mapped_path);
    }

    string AssetManager::Combine(string path1,string path2)
    {
        auto it =path1.end()-1;
        if(*it=='/')
            path1.pop_back();

        it=path2.begin();
        if(*it!='/')
            path2.insert(it,'/');
        return path1+path2;
    }

    string AssetManager::GetDirectoryName(string path)
    {
        auto pos = path.rfind('/');
        return path.substr(0,pos);
    }

    string AssetManager::GetFileName(string path)
    {
        auto pos = path.rfind('/');
        return path.substr(pos+1);
    }

    string AssetManager::GetBestMatchPath(string s1)
    {
        string&& best="";
        for(auto pair : m_mapped_fs)
        {
            if(s1.find(pair.first)!=string::npos)
            {
                if(pair.first.size()>best.size())
                    best=pair.first;
            }
        }
        return best;
    }

    IFileSystem* AssetManager::FindMappedFileSystem(const string& file,string* out_path)
    {
        string path=GetBestMatchPath(file);
        if(out_path!=nullptr)
            *out_path=file.substr(path.size());
        return m_mapped_fs[path];
    }

    AssetManager::~AssetManager()
    {
        for (auto pair : m_mapped_fs) {
            delete pair.second;
        }
    }
}
