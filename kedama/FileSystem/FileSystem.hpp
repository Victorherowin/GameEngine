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

        class KEDAMA_API FileSystem
        {
        public:
            virtual ~FileSystem() {}

            virtual IStream* CreateIStream(const string& file, ios_base::openmode mode)=0;
			virtual OStream* CreateOStream(const string& file, ios_base::openmode mode) = 0;
			virtual IOStream* CreateIOStream(const string& file, ios_base::openmode mode) = 0;
            virtual bool Exist(const string& file)=0;
            virtual const string& GetFileSystemType()=0;

            virtual void Mount(const string& path,FileSystem* fs);
            virtual void Unmount(const string& path);

        };
    }
}

#endif
