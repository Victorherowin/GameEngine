#include "LocalFileSystem.hpp"
#include <sys/stat.h>

namespace Kedama::File
{

	static bool FileExist(const string& file)
    {
        FILE* fp = fopen(file.c_str(), "e");
        if (fp == nullptr)
            return false;
        fclose(fp);
        return true;
    }


    static bool DirectoryExist(const string& dir)
    {
#ifdef _WIN32
        struct _stat file_stat;
        if ((_stat(dir.c_str(), &file_stat) == 0) && (file_stat.st_mode & _S_IFDIR)) {
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

    IStream* LocalFileSystem::CreateIStream(const string& file, ios_base::openmode mode)
    {
        for (auto&& it : m_mount_mapping_table) {
            string::size_type pos = file.find(it.first);
            if (pos != string::npos) {
                FileSystem* fs = m_mount_mapping_table[it.first];
                IStream* s = fs->CreateIStream(file.substr(pos, string::npos), mode);
                return s;
            }
        }

        return new ifstream(m_path+file, mode);
    }

	OStream* LocalFileSystem::CreateOStream(const string& file, ios_base::openmode mode)
	{
		for (auto&& it : m_mount_mapping_table) {
			string::size_type pos = file.find(it.first);
			if (pos != string::npos) {
				FileSystem* fs = m_mount_mapping_table[it.first];
				OStream* s = fs->CreateOStream(file.substr(pos, string::npos), mode);
				return s;
			}
		}

		return new ofstream(m_path+file, mode);
	}

	IOStream* LocalFileSystem::CreateIOStream(const string& file, ios_base::openmode mode)
	{
		for (auto&& it : m_mount_mapping_table) {
			string::size_type pos = file.find(it.first);
			if (pos != string::npos) {
				FileSystem* fs = m_mount_mapping_table[it.first];
				IOStream* s = fs->CreateIOStream(file.substr(pos, string::npos), mode);
				return s;
			}
		}

		return new fstream(m_path + file, mode);
	}

    bool LocalFileSystem::Exist(const string& file)
    {
		for (auto&& it : m_mount_mapping_table) {
			string::size_type pos = file.find(it.first);
			if (pos != string::npos) {
				FileSystem* fs = m_mount_mapping_table[it.first];
				return fs->Exist(file.substr(pos, string::npos));
			}
		}
        return !ifstream(m_path+file).bad();
    }

    void LocalFileSystem::Mount(const string& path, FileSystem* fs)
    {
        for (auto&& it : m_mount_mapping_table) {
            string::size_type pos = path.find(it.first);
            if (pos != string::npos) {
                FileSystem* mapping_fs = m_mount_mapping_table[it.first];
                mapping_fs->Mount(path.substr(pos, string::npos), fs);
                return;
            }
        }

        if (FileExist(m_path+path))
            throw runtime_error("Mount Failed: File Exist!");
        else if (DirectoryExist(m_path+path))
            throw runtime_error("Mount Failed: Directory Exist!");

        m_mount_mapping_table[path] = fs;
    }

    void LocalFileSystem::Unmount(const string& path)
    {
        for (auto&& it : m_mount_mapping_table) {
            string::size_type pos = path.find(it.first);
            if (pos != string::npos) {
                FileSystem* mapping_fs = m_mount_mapping_table[it.first];
                mapping_fs->Unmount(path.substr(pos, string::npos));
                return;
            }
        }

        if (FileExist(m_path+path))
            throw runtime_error("Unmount Failed: Is File.");
        else if (DirectoryExist(m_path + path))
            throw runtime_error("Unmount Failed: Is Directory.");

        auto it = m_mount_mapping_table.find(path);
        delete it->second;
        m_mount_mapping_table.erase(it);
    }

    const string& LocalFileSystem::GetFileSystemType()
    {
        static string str("Local");
        return str;
    }

}
