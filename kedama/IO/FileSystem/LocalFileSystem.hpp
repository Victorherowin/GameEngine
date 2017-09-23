#ifndef _H_LOCALFILESYSTEM
#define _H_LOCALFILESYSTEM

#include "../../Define.hpp"

#include "IFileSystem.hpp"
#include <map>
#include <list>

namespace Kedama
{
	namespace FileSystem
	{
		class LocalFile;

        class KEDAMA_API LocalFileSystem:public IFileSystem
		{
			public:
			LocalFileSystem(const string& path);
			~LocalFileSystem();
			
			IStream* OpenRead(const string& file)override;
			IStream* OpenWrite(const string& file) override;
			IStream* Open(const string& file)override;
            const string& GetFileSystemType()override;

			private:
			string m_path;
            map<string,IFileSystem*> m_mount_mapping_table;
		};
	}
}

#endif
