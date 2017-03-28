#ifndef _H_LOCALFILESYSTEM
#define _H_LOCALFILESYSTEM

#include "../Define.hpp"

#include "Interface/IFileSystem.hpp"
#include <map>
#include <list>

namespace Kedama
{
	namespace File
	{
		class LocalFile;
		struct Node;
		
        class KEDAMA_API LocalFileSystem:public IFileSystem
		{
			public:
			LocalFileSystem(const string& path);
			~LocalFileSystem();
			
            IFile* Open(const string& file,AccessFlag flag)override;
			void Close(IFile* file)override;
			bool Opening(IFile* fp)override;
            const string& GetFileType()override;
			
			bool Exist(const string& path);
            void Mount(const string& path,IFileSystem* filesystem);
			
			private:
			
			Node* Find(const string& path);
			void ScanDirectory(Node* node,const string& path);
			
			private:
			string m_path;
            list<IFileSystem*> m_fs_list;
			map<string,list<LocalFile*>> m_opening_files;
			Node* m_root;
		};
	}
}

#endif
