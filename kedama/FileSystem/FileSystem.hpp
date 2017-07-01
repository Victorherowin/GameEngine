#ifndef _H_FILESYSTEM
#define _H_FILESYSTEM

#include "../Define.hpp"
#include "../Include.hpp"

#include "Stream.hpp"

namespace Kedama
{
    namespace File
    {
        using namespace std;

        enum AccessFlag
        {
            Read = 1, Write = 2, Create = 4
        };

        class KEDAMA_API FileSystem
        {
        public:
            virtual ~FileSystem() {}

            virtual Stream* Open(const string& file, AccessFlag flag)=0;
            virtual bool Exist(const string& file)=0;
            virtual const string& GetFileSystemType()=0;

            virtual void Mount(const string& path,FileSystem* fs);
            virtual void Unmount(const string& path);

        };
    }
}

#endif
