#ifndef FILEMANAGER
#define FILEMANAGER

#include "../utility/Singleton.hpp"

#include "../Include.hpp"
#include "IFileSystem.hpp"

namespace Kedama
{
    class FileManager:public Singleton<FileManager>
    {
    public:
        void Mount(const string& mount_point32_t,IFileSystem* ifs);
        void Unmount(const string& mount_point32_t);
        IFileSystem::File* Open(const string& path,IFileSystem::OpenMode mode);
        void Close(IFileSystem::File* file);
    private:
        map<string,IFileSystem*> m_file_system_map;
    };
}

#endif
