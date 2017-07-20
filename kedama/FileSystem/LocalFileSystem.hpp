#ifndef _H_LOCALFILESYSTEM
#define _H_LOCALFILESYSTEM

#include "../Define.hpp"

#include "FileSystem.hpp"
#include <map>
#include <list>

namespace Kedama
{
	namespace File
	{
		class LocalFile;

        class KEDAMA_API LocalFileSystem:public FileSystem
		{
			public:
			LocalFileSystem(const string& path);
			~LocalFileSystem();
			
			IStream* CreateIStream(const string& file, ios_base::openmode mode)override;
			OStream* CreateOStream(const string& file, ios_base::openmode mode) override;
			IOStream* CreateIOStream(const string& file, ios_base::openmode mode)override;
            const string& GetFileSystemType()override;
			
			bool Exist(const string& path)override;
            void Mount(const string& path,FileSystem* filesystem)override;
            void Unmount(const string& path)override;

			private:
			string m_path;
            map<string,FileSystem*> m_mount_mapping_table;
		};
	}
}

#endif
