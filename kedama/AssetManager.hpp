#ifndef ASSETMANAGER
#define ASSETMANAGER

#include "Include.hpp"
#include "Define.hpp"

#include "RenderSystem/Model.hpp"
#include "IO/IStream.hpp"
#include "IO/FileSystem/IFileSystem.hpp"

namespace Kedama
{
    using namespace std;
    using namespace IO;
    using namespace FileSystem;

    class KEDAMA_API AssetManager
    {
    public:
        ~AssetManager();

        IStream* OpenRead(const string& file);
        IStream* OpenWrite(const string& file);
        IStream* Open(const string& file);
        void Map(string path, IFileSystem* fs);
        void Unmap(string path);
        bool FileExist(const string& file);
        bool DirectorExist(const string& path);
        static string Combine(string path1, string path2);
        static string GetDirectoryName(string path);

        static string GetFileName(string path);

    private:
        IFileSystem* FindMappedFileSystem(const string& file, string* out_path);

        string GetBestMatchPath(string path);

        map<string, IFileSystem*> m_mapped_fs;
    };
}

#endif
