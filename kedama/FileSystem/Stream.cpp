//
// Created by moe on 2017-07-01.
//

#include "Stream.hpp"

namespace Kedama
{
    namespace File
    {
        int Kedama::File::Stream::Write(const void* data, int size)
        {
            throw std::runtime_error("No Implement");
            return 0;
        }

        void Stream::Seek(SeekMode type, int offset)
        {
            throw std::runtime_error("No Implement");
        }
    }
}


