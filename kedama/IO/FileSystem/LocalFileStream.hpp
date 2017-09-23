//
// Created by moe on 2017-09-23.
//

#ifndef KEDAMA_LOCALFILESTREAM_HPP
#define KEDAMA_LOCALFILESTREAM_HPP

#include "../IStream.hpp"
#include "../../Include.hpp"

namespace Kedama::File
{
    using namespace Kedama::IO;
    using namespace std;

    class LocalFileStream:public IStream
    {
    public:
        LocalFileStream(const string& file,const string& mode);
        ~LocalFileStream() override;

        bool CanWrite() override;
        bool CanRead() override;
        bool CanSeek() override;

        bool Eof() override;
        void Close() override;

        void Read(uint8_t* data, size_t length) override;
        void Write(const uint8_t* data, size_t length) override;
        void Seek(StreamSeek type, size_t offset) override;

    private:
        FILE* m_fp;
        bool m_can_read=false;
        bool m_can_write=false;
    };
}

#endif //KEDAMA_LOCALFILESTREAM_HPP
