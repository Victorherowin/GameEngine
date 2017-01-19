#include "LocalFileSystem.hpp"

namespace Kedama {

    IFileSystem::File* LocalFileSystem::Open(const string& path,OpenMode mode)
    {
        static std::ios_base::openmode openmode_table[4]={};
        string local_path;
        local_path.push_back(path[1]);
        local_path.push_back(':');
#ifdef _WIN32
        for(auto it=path.begin()+2;it!=path.end();++it)
        {
            if(*it=='/')
                local_path.push_back('\\');
            else
                local_path.push_back(*it);
        }
#else
        local_path=path;
#endif
        return new LocalFile(path);
    }

    void LocalFileSystem::Close(File *file)
    {
        delete dynamic_cast<LocalFile*>(file);
    }

    LocalFileSystem::LocalFile::LocalFile(const string& path):m_file(path)
    {
    }

    bool LocalFileSystem::LocalFile::Eof()
    {
        return m_file.eof();
    }

    void LocalFileSystem::LocalFile::Read(void *data, int32_t size)
    {
        m_file.read((char*)data,size);
    }

    void LocalFileSystem::LocalFile::Write(const void *data, int32_t size)
    {
        m_file.write((const char*)data,size);
    }

    void LocalFileSystem::LocalFile::Seek(SeekMode mode, int32_t offset)
    {
        static std::ios_base::seekdir seekmode_table[3]={std::ios_base::beg,std::ios_base::cur,std::ios_base::end};
        m_file.seekg(offset,seekmode_table[(int32_t)mode]);
    }
}
