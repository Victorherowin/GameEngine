//
// Created by moe on 2017-09-23.
//

#include "LocalFileStream.hpp"
#include "../../Exception/RuntimeException.hpp"

namespace Kedama::File
{
    LocalFileStream::LocalFileStream(const string& file, const string& mode)
    {
        m_fp=fopen(file.c_str(),mode.c_str());
        for(auto c : mode)
        {
            if(c=='w'||c=='a')
                m_can_write=true;
            if(c=='r')
                m_can_read=true;
        }
    }

    LocalFileStream::~LocalFileStream()
    {
        Close();
    }

    bool LocalFileStream::CanWrite()
    {
        return m_can_write;
    }

    bool LocalFileStream::CanRead()
    {
        return m_can_read;
    }

    bool LocalFileStream::CanSeek()
    {
        return true;
    }

    bool LocalFileStream::Eof()
    {
        return feof(m_fp)!=0;
    }

    void LocalFileStream::Close()
    {
        fclose(m_fp);
    }

    void LocalFileStream::Read(uint8_t* data, size_t length)
    {
        if(!m_can_read)
            throw Exception::RuntimeException("Cann't Read");
        fread(data,1,length,m_fp);
    }

    void LocalFileStream::Write(const uint8_t* data, size_t length)
    {
        if(!m_can_write)
            throw Exception::RuntimeException("Cann't Write");
        fwrite(data,1,length,m_fp);
    }

    void LocalFileStream::Seek(StreamSeek type, size_t offset)
    {
        static int _table[]{SEEK_CUR,SEEK_SET,SEEK_END};
        fseek(m_fp,offset,_table[(int)type]);
    }
}