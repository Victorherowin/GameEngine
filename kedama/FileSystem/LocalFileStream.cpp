#include "LocalFile.hpp"

namespace Kedama
{
    namespace File
    {
        LocalFileStream::LocalFileStream(const string& file, AccessFlag flag)
        {
            string access_flag;
            if (flag & AccessFlag::Create)
                access_flag = "w";
            if (flag & AccessFlag::Read)
                access_flag += "r";
            if (flag & AccessFlag::Write)
                access_flag += "a";
            m_fp = fopen(file.c_str(), access_flag.c_str());
            fseek(m_fp, 0, SEEK_SET);
            int pos = file.rfind('/');
            if (pos != string::npos)
                m_name = file.substr(pos + 1);
            else
                m_name = file;
        }

        LocalFileStream::~LocalFileStream()
        {
            fclose(m_fp);
        }

        const string& LocalFileStream::GetType()
        {
            static string str("LocalFile");
            return str;
        }

        bool LocalFileStream::Eof()
        {
            return feof(m_fp);
        }

        int LocalFileStream::Read(void* data, int size)
        {
            return fread(data, 1, size, m_fp);
        }

        int LocalFileStream::Write(const void* data, int size)
        {
            return fwrite(data, 1, size, m_fp);
        }

        void LocalFileStream::Seek(SeekMode type, int offset)
        {
            fseek(m_fp, offset, (int) type);
        }

        int LocalFileStream::Tell()
        {
            return ftell(m_fp);
        }

        bool LocalFileStream::IsBad()
        {
            return m_fp== nullptr;
        }

        void LocalFileStream::Close()
        {
            fclose(m_fp);
        }
    }
}
