#include "LocalFileSystem.hpp"
#include "LocalFileStream.hpp"
#include <sys/stat.h>

namespace Kedama
{
    namespace File
    {

        bool FileExist(const string& file)
        {
            FILE* fp = fopen(file.c_str(),"e");
            if(fp==nullptr)
                return false;
            fclose(fp);
            return true;
        }


        bool DirectoryExist(const string& dir)
        {
#ifdef _WIN32
            struct _stat file_stat;
            if ((_stat(dir.c_str(), &file_stat) == 0) && (file_stat.st_mode & _S_IFDIR ))
            {
                return true;
            }
#else
            struct stat file_stat;
            if ((stat(dir.c_str(), &file_stat) == 0) && S_ISDIR(file_stat.st_mode))
            {
                return true;
            }
#endif
            return false;
        }

        LocalFileSystem::LocalFileSystem(const string& path) : m_path(path)
        {
        }

        LocalFileSystem::~LocalFileSystem()
        {
        }

        Stream* LocalFileSystem::Open(const string& file, AccessFlag flag)
        {
            for(auto&& it : m_mount_mapping_table)
            {
                string::size_type pos=file.find(it.first);
                if(pos!=string::npos)
                {
                    FileSystem* fs=m_mount_mapping_table[it.first];
                    Stream* s=fs->Open(file.substr(pos,string::npos),flag);
                    return s;
                }
            }

            return new LocalFileStream(file,flag);
        }

        bool LocalFileSystem::Exist(const string& path)
        {
            return !LocalFileStream(path,AccessFlag::Read).IsBad();
        }

        void LocalFileSystem::Mount(const string& path, FileSystem* fs)
        {
            for(auto&& it : m_mount_mapping_table)
            {
                string::size_type pos=path.find(it.first);
                if(pos!=string::npos)
                {
                    FileSystem* mapping_fs=m_mount_mapping_table[it.first];
                    mapping_fs->Mount(path,fs);
                    return;
                }
            }

            if(FileExist(path))
                throw runtime_error("Mount Failed: File Exist!");
            else if(DirectoryExist(path))
                throw runtime_error("Mount Failed: Directory Exist!");

            m_mount_mapping_table[path]=fs;
        }

        void LocalFileSystem::Unmount(const string& path)
        {
            for(auto&& it : m_mount_mapping_table)
            {
                string::size_type pos=path.find(it.first);
                if(pos!=string::npos)
                {
                    FileSystem* mapping_fs=m_mount_mapping_table[it.first];
                    mapping_fs->Unmount(path);
                    return;
                }
            }

            if(FileExist(path))
                throw runtime_error("Unmount Failed: Is File.");
            else if(DirectoryExist(path))
                throw runtime_error("Unmount Failed: Is Directory.");

            auto it=m_mount_mapping_table.find(path);
            delete it->second;
            m_mount_mapping_table.erase(it);
        }

        const string& LocalFileSystem::GetFileSystemType()
        {
            static string str("Local");
            return str;
        }
    }
}
