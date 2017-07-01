#ifndef _H_LOCALFILESTREAM
#define _H_LOCALFILESTREAM

#include "../Define.hpp"

#include "Stream.hpp"
#include "FileSystem.hpp"
#include <string>
#include <cstdio>

namespace Kedama
{
    namespace File
    {
        using namespace std;

        class KEDAMA_API LocalFileStream : public Stream
        {
        public:
            LocalFileStream(const string& file, AccessFlag flag);

            ~LocalFileStream();

            const string& GetType() override;
            bool Eof() override;
            bool IsBad()override;
            int Read(void* data, int size) override;
            int Write(const void* data, int size) override;
            void Seek(SeekMode type, int offset) override;
            int Tell() override;
            void Close() override;

            inline const string& GetName() { return m_name; }

        private:
            string m_name;
            FILE* m_fp;
        };
    }
}

#endif
