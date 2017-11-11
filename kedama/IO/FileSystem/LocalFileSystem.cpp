#include "LocalFileSystem.hpp"
#include "LocalFileStream.hpp"
#include "../Path.hpp"
#include <sys/stat.h>

namespace Kedama::FileSystem
{
    using namespace Kedama::File;

    LocalFileSystem::LocalFileSystem(const string& path) : m_path(path)
    {
    }

    LocalFileSystem::~LocalFileSystem()
    {
    }

    IStream* LocalFileSystem::OpenRead(const string& file)
    {
        return new LocalFileStream(Path::Combine(m_path,file), "rb");
    }

	IStream* LocalFileSystem::OpenWrite(const string& file)
	{
		return new LocalFileStream(Path::Combine(m_path,file), "wb");
	}

	IStream* LocalFileSystem::Open(const string& file)
	{		return new LocalFileStream(Path::Combine(m_path,file), "rb+");
	}

    const string& LocalFileSystem::GetFileSystemType()
    {
        static string str("LocalFileSystem");
        return str;
    }

}
