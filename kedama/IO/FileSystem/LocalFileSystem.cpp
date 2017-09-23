#include "LocalFileSystem.hpp"
#include "LocalFileStream.hpp"
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
        return new LocalFileStream(m_path+file, "r");
    }

	IStream* LocalFileSystem::OpenWrite(const string& file)
	{
		return new LocalFileStream(m_path+file, "w");
	}

	IStream* LocalFileSystem::Open(const string& file)
	{
		return new LocalFileStream(m_path + file, "ra+");
	}

    const string& LocalFileSystem::GetFileSystemType()
    {
        static string str("LocalFileSystem");
        return str;
    }

}
