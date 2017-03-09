#ifndef _H_LOCALFILE
#define _H_LOCALFOLE

#include "../Define.hpp"

#include "Interface/IFile.hpp"
#include "Interface/IFileSystem.hpp"
#include <string>
#include <cstdio>

namespace Kedama
{
	namespace File
	{
		using namespace std;
		
		class KEDAMA_API LocalFile:public IFile
		{
			public:
			LocalFile(const string& file,AccessFlag flag);
			~LocalFile();
			
			bool AvailableWrite()override;
            const string& GetType()override;
			
			bool Eof()override;
			int Read(void* data,int size)override;
			int Write(const void* data,int size)override;
			void Seek(SeekType type,int offset)override;
			int Tell()override;
			
			inline const string& GetName(){return m_name;}
			
			private:
			string m_name;
			FILE* m_fp;
		};
	}
}

#endif
