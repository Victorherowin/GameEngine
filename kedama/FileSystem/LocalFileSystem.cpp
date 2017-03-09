#include "LocalFileSystem.hpp"
#include "LocalFile.hpp"

#include <regex>

#ifdef _WIN32
#include <windows.h>
#define SLASH "\\"
#else
#include <dirent.h>
#define SLASH "/"
#endif

namespace Kedama
{
  namespace File
  {
    struct Node
    {
      enum class Type
      {
        File,Directory,MountPoint
      };

      Node(Node* parent,const string& name,Type type):Name(name),Type(type){}
      ~Node()
      {
        for(auto& obj:Children)
          delete obj.second;
      }

      string GetFullName()
      {
        string full_name;
        for(Node* i=this;i!=nullptr;i=i->Parent)
        {
          full_name=string("/")+i->Name+full_name;
        }
        full_name.erase(full_name.begin());
        return full_name;
      }

      Node* Parent=nullptr;
      string Name;
      Type Type;
      IFileSystem* FileSystem=nullptr;
      map <string,Node*> Children;
    };

    LocalFileSystem::LocalFileSystem(const string& path):m_path(path)
    {
      m_root=new Node(nullptr,"/",Node::Type::Directory);
      ScanDirectory(m_root,m_path);
    }

    LocalFileSystem::~LocalFileSystem()
    {
      delete m_root;
      for(auto& files:m_opening_files)
        for(auto file:files.second)
          delete file;
    }

    IFile* LocalFileSystem::Open(const string& file,AccessFlag flag)
    {
      Node* node=nullptr;
      if(!(flag&AccessFlag::Create))
      {
        node=Find(file);
        if(node==nullptr)
          throw runtime_error("File No Found");
        if(node->Type==Node::Type::MountPoint)
          return node->FileSystem->Open(file.substr(file.find(node->GetFullName())+node->Name.size(),string::npos),flag);
        if(node->Type==Node::Type::Directory)
          throw runtime_error("Path Is Directory");
      }

      string local_file_name=file;
#ifdef _WIN32
      for(auto& tmp:local_file_name)
        if(tmp=='/')tmp='\\';
#endif
      local_file_name=m_path+SLASH+local_file_name;
      LocalFile* lfile=new LocalFile(local_file_name,flag);

      m_opening_files[lfile->GetName()].push_back(lfile);

      return lfile;
    }

    bool LocalFileSystem::Opening(IFile* fp)
    {
      for(auto files:m_opening_files)
        for(auto file:files.second)
          if(file==fp)return true;
      for(auto fs:m_fs_list)
      {
        if(fs->Opening(fp))
          return true;
      }
      return false;
    }

    void LocalFileSystem::Close(IFile* fp)
    {
      if(fp->GetType()=="LocalFile")
      {
        LocalFile* local_file=static_cast<LocalFile*>(fp);
        list<LocalFile*>& files=m_opening_files[local_file->GetName()];
        for(auto it=files.begin();it!=files.end();)
          if(*it==fp)
          {
            delete *it;
            it=files.erase(it);
            return;
          }
          else
            ++it;
      }
      for(auto fs:m_fs_list)
      {
        if(fs->Opening(fp))
        {
          fs->Close(fp);
          return;
        }
      }
      throw runtime_error("Type Error");
    }
#ifdef _WIN32
    void LocalFileSystem::ScanDirectory(Node* node,const string& path)
    {
      WIN32_FIND_DATA find_file_data;
      HANDLE h_find;
      h_find=FindFirstFile((path+"\\*").c_str(),&find_file_data);
      if(h_find==INVALID_HANDLE_VALUE)
      {
        throw runtime_error("path error");
      }

      do
      {
        if(string(find_file_data.cFileName)=="."||string(find_file_data.cFileName)=="..")continue;
        if(find_file_data.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
        {
          Node* c_node=new Node(node,find_file_data.cFileName,Node::Type::Directory);
          ScanDirectory(c_node,path+SLASH+find_file_data.cFileName);
          node->Children[find_file_data.cFileName]=c_node;
          continue;
        }
        Node* c_node=new Node(node,find_file_data.cFileName,Node::Type::File);
        node->Children[find_file_data.cFileName]=c_node;
      }while(FindNextFile(h_find,&find_file_data)!=0);
      FindClose(h_find);
    }
#else
    void LocalFileSystem::ScanDirectory(Node* node,const string& path)
    {
      struct dirent *entry;
      DIR* dir=opendir(m_path.c_str());

      if(dir==nullptr)
      {
        throw runtime_error("path error");
      }

      while(entry=readdir(dir))
      {
        if(string(entry->d_name)=="."||string(entry->d_name)=="..")continue;
        if(entry->d_type==DT_DIR)
        {
          Node* c_node=new Node(node,entry->d_name,Node::Type::Directory);
          ScanDirectory(c_node,path+SLASH+entry->d_name);
          node->Children[entry->d_name]=c_node;
          continue;
        }
        Node* c_node=new Node(node,entry->d_name,Node::Type::File);
        node->Children[entry->d_name]=c_node;
      }

      closedir(dir);
    }
#endif

    bool LocalFileSystem::Exist(const string& path)
    {
      return Find(path)?true:false;
    }

    Node* LocalFileSystem::Find(const string& path)
    {
      if(path=="")return nullptr;
      if(path=="/")return m_root;

      string _path=path.substr(1);

      regex rg("/");
      sregex_token_iterator rti(_path.begin(),_path.end(),rg,-1);
      sregex_token_iterator end;
      Node* node=m_root;

      while(rti!=end)
      {
        string name=*rti;
        auto it=node->Children.find(name);
        if(node->Type==Node::Type::MountPoint)
          return node;
        if(it!=node->Children.end())
          node=it->second;
        else
          return nullptr;
        ++rti;
      }
      return node;
    }

    void LocalFileSystem::Mount(const string& path,IFileSystem* fs)
    {
      string parent_path=path.substr(0,path.rfind("/")+1);
      string name=path.substr(path.rfind("/")+1);
      Node* pnode=Find(parent_path);
      Node* cnode=new Node(pnode,name,Node::Type::MountPoint);
      cnode->FileSystem=fs;
      pnode->Children[name]=cnode;

      m_fs_list.push_back(fs);
    }

    const string& LocalFileSystem::GetFileType()
    {
      static string str("LocalFile");
      return str;
    }
  }
}
