#include <Engine.hpp>
#include <FileSystem/LocalFileSystem.hpp>
#include <RenderSystem/RendererFactoryManager.hpp>
#include <RenderSystem/GL/GLRendererFactory.hpp>
#include <RenderSystem/Interface/IRendererFactory.hpp>
#include <RenderSystem/Interface/IWindow.hpp>
#include <RenderSystem/CommandBuffer.hpp>
#include <RenderSystem/PropertyValue.hpp>
#include <Log.hpp>

#include <string>
#include <thread>
#include <chrono>

#include <GL/glew.h>

#include <SDL2/SDL.h>
#include <utility/Exception/ExceptionCommon.hpp>

#undef main

using namespace std;
using namespace std::chrono;
using namespace Kedama;
using namespace Kedama::GL;
using namespace File;

string vs_shader_src=
R"(#version 450 core
   layout(location = 0)in vec4 pos;
   layout(location = 1)in vec4 uv;
   out vec4 f_uv;
   layout(std140)uniform Model{mat4 model_matrix[1000];};
   layout(std140)uniform Camera{mat4 view_matrix;mat4 projection_matrix;mat4 view_projection;};
   void VS_main()
   {
    gl_Position=view_projection*model_matrix[gl_InstanceID]*pos;
    f_uv=pos;
   })";
string fs_shader_src=R"(
   #version 450 core
   in vec4 f_uv;
   out vec4 color;
   layout(binding = 0)uniform sampler2D kedama_tex;
   void FS_main()
   {
     color=vec4(f_uv.xyz,1.0);
   }
)";


vector<uint32> index({0,1,2});
vector<vec3> tri_vertex({vec3(0.0f,1.0f,0.0f),vec3(1.0f,-1.0f,0.0f),vec3(-1.0f,-1.0f,0.0f)});
vector<uint32> floor_index({0,1,2,0,3,2});

void func()
{
	int* p = nullptr;
	*p = 0;
}

int32_t main(int32_t argc,char** argv)
{
    Exception::Exception::Init(argv[0]);
    Exception::Exception e;
    e.PrintStackTrace(cerr);
	func();
    RendererFactoryManager::GetSingleton().RegisterFactory("GLRenderSystem",new GLRenderSystemFactory());
    Engine engine("GLRenderSystem");
    auto& irs = engine.GetRenderSystem();
    auto& sm=engine.GetSceneManager();
    auto&& irsf=engine.GetRendererFactory();

 /*   LocalFileSystem* fs=new LocalFileSystem(R"(D:\Project-CPP\build-MSN-Live-Test-unknown-Debug)");
    IFileSystem* fs2=new LocalFileSystem(R"(D:\Project-CPP\build-FindBaseAddress-unknown-Debug)");
    fs->Mount("/fs2",fs2);
    IFile* fp=fs->Open("/fs2/CMakeFiles/test.txt",AccessFlag::Read);
    char buf[128];
    memset(buf,0,128);
    fp->Read(buf,128);
    printf("%s\n",buf);
    fs->Close(fp);*/

    IWindow* win=irs->GetWindow();
    win->Create("ForwardRender",800,600);

    GameObject obj,obj2;
    obj.SetWorldPosition(vec3(0.0f,0.5f,0.0f));
    obj.AddChildren(&obj2);
    obj2.SetWorldPosition(vec3(2.5,0.0,0.5));
    obj2.SetScale(1.0,2.0,1.0);
    Camera camera("TestCamera");
    StaticMesh test_mesh(tri_vertex.size(),index.size());
	test_mesh.SetIndices(index);
	test_mesh.SetPositions(tri_vertex);

    Material* test_material=Material::MakeDefaultMaterial();
    /*DefaultMaterial test_material;
    IShader* shader=irsf->CreateShader();
    shader->SetFragmentShaderSource(fs_shader_src);
    shader->SetVertexShaderSource(vs_shader_src);
    shader->Compile();

    test_material.SetAmbient(vec3(0.0f,1.0f,1.0f));
    test_material.Update();*/

    //Pass* pass=test_material.CreatePass();
    //test_material.UsePass(pass);
    //pass->shader=shader;
    camera.Move(vec3(1.0,0.0,10.0));
    camera.SetPerspective(45.0f,800.0f/600.0f,0.1f,1000.0f);
    camera.LookAt(&obj);

    auto& rs=Engine::GetSingletonPtr()->GetRenderSystem();
    KEDAMALOG("Init Engine\n");

    bool quit=false;
    SDL_Event ev;
    rs->SetCamera(&camera);
    int t=0;
    while(!quit)
    {
      while(SDL_PollEvent(&ev))
      {
        if(ev.type==SDL_QUIT)quit=true;
      }
      obj.Rotate(vec3(0,1,0),0.1f/glm::pi<float>());

      CommandBuffer cb;
      cb.AddRenderCommand(&obj,test_mesh.GetMeshBuffer(),test_material);
      cb.AddRenderCommand(&obj2,test_mesh.GetMeshBuffer(),test_material);
      obj2.Move(vec3(sin(t++*0.05)*0.5,0,0));
      obj.Update();

	  test_material->GetProperty<vec4>("color") = lerp(vec4(1.0f,0.5f,0.4f,1.0f),vec4(0.4f,1.0f,0.8f,1.0f),t*0.01f);
      rs->Clear();
      rs->Render(cb);
      rs->SwapBuffer();
      this_thread::sleep_for(chrono::milliseconds(33));
    }

    return 0;
}
