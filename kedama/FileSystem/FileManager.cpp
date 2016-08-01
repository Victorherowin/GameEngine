#include "FileManager.hpp"

namespace Kedama
{
    void FileManager::Mount(const string& mount_point32_t,IFileSystem* ifs)
    {
        if(mount_point32_t[0]!='/')throw runtime_error("Invalid path");
        string key(mount_point32_t.c_str()+1);
        if(m_file_system_map.find(key)==m_file_system_map.end())
        {
            m_file_system_map[key]=ifs;
        }
    }

    void FileManager::Unmount(const string& mount_point32_t)
    {
        if(mount_point32_t[0]!='/')throw runtime_error("Invalid path");
        string key(mount_point32_t.c_str()+1);

        auto it=m_file_system_map.find(key);
        if(it!=m_file_system_map.end())
        {
            m_file_system_map.erase(it);
        }
        else
        {
            throw runtime_error("Invalid path");
        }
    }

    IFileSystem::File* FileManager::Open(const string& path,IFileSystem::OpenMode mode)
    {
        string key;
        string file_path;
        if(path[0]!='/')throw runtime_error("Invalid path");
        auto it=path.begin()+1;
        for(;it!=path.end()&&*it!='/';++it)
        {
            key.push_back(*it);
        }

        if(*it=='/')--it;

        for(;it!=path.end();++it)
        {
            file_path.push_back(*it);
        }
        if(m_file_system_map.find(key)==m_file_system_map.end())return nullptr;
        return m_file_system_map[key]->Open(file_path,mode);
    }
}
