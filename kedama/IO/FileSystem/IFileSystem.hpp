#ifndef _H_FILESYSTEM
#define _H_FILESYSTEM

#include "../../Define.hpp"
#include "../../Include.hpp"

#include "../IStream.hpp"

namespace Kedama
{
    using namespace IO;

    namespace FileSystem
    {
        using namespace std;

        class KEDAMA_API IFileSystem
        {
        public:
            virtual ~IFileSystem() {}

            virtual IStream* OpenRead(const string& file)=0;
			virtual IStream* OpenWrite(const string& file) = 0;
			virtual IStream* Open(const string& file) = 0;
            virtual const string& GetFileSystemType()=0;
        };
    }
}

#endif
