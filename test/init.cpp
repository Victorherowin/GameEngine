#include <Engine.hpp>
#include <RenderSystem/RendererFactoryManager.hpp>
#include <RenderSystem/GL/GLRendererFactory.hpp>
#include <RenderSystem/Interface/IRendererFactory.hpp>
#include <RenderSystem/Interface/IWindow.hpp>
#include <RenderSystem/CommandBuffer.hpp>
#include <Log.hpp>

#include <string>
#include <thread>
#include <chrono>

#include <GL/glew.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#undef main

using namespace std;
using namespace std::chrono;
using namespace Kedama;
using namespace Kedama::GL;

string vs_shader_src=
R"(#version 450 core
   layout(std140)uniform Camera
   {
      mat4 kedama_view_matrix;
      mat4 kedama_projection_matrix;
      mat4 kedama_view_projection_matrix;
   };

   layout(location = 0)in vec4 pos;
   layout(location = 1)in vec4 uv;
   out vec2 f_uv;
   void main()
   {
    gl_Position=pos;
    f_uv=uv.xy;
   })";
string fs_shader_src=R"(
   #version 450 core
   in vec2 f_uv;
   layout(binding = 0)uniform sampler2D kedama_tex;
   void main()
   {
     gl_FragColor=vec4(1.0,0.0,1.0,1.0);
   }
)";


vector<uint32> index({0,1,2});
vector<vec3> tri_vertex({vec3(0.0f,1.0f,0.0f),vec3(1.0f,-1.0f,0.0f),vec3(-1.0f,-1.0f,0.0f)});
vector<uint32> floor_index({0,1,2,0,3,2});

int32_t main(int32_t argc,char** argv)
{
    RendererFactoryManager::GetSingleton().RegisterFactory("GLRenderSystem",new GLRenderSystemFactory());
    Engine engine("GLRenderSystem");
    RenderSystem* irs = engine.GetRenderSystem();
    SceneManager* sm=engine.GetSceneManager();
    IRendererFactory* irsf=engine.GetRendererFactory();
    IWindow* win=irs->GetWindow();
    win->Create("ForwardRender",800,600);

    GameObject obj;
    Camera camera("TestCamera");
    Mesh test_mesh;
    Material test_material;
    Shader* vs=Engine::GetSingletonPtr()->GetRendererFactory()->CreateShader(Shader::ShaderType::VERTEX_SHADER,vs_shader_src);
    Shader* fs=Engine::GetSingletonPtr()->GetRendererFactory()->CreateShader(Shader::ShaderType::FRAGMENT_SHADER,fs_shader_src);

    test_mesh.SetIndices(index);
    test_mesh.SetVertices(tri_vertex);
    test_mesh.Update();
    Pass* pass=test_material.CreatePass();
    test_material.UsePass(pass);
    pass->fragment_shader=fs;
    pass->vertex_shader=vs;
    camera.GetTansform()->Move(vec3(1.0,0.0,1.0));
    camera.SetPerspective(45.0f,800.0f/600.0f,0.1f,1000.0f);
    camera.LookAt(&obj);


    CommandBuffer cb;
    cb.AddForwardRenderCommand(obj.GetTansform(),&test_mesh,&test_material);

    RenderSystem* rs=Engine::GetSingletonPtr()->GetRenderSystem();

    bool quit=false;
    SDL_Event ev;
    rs->SetCamera(&camera);
    while(!quit)
    {
      while(SDL_PollEvent(&ev))
      {
        if(ev.type==SDL_QUIT)quit=true;
      }
      rs->Clear();
      rs->Render(cb);
      rs->SwapBuffer();
      this_thread::sleep_for(chrono::milliseconds(50));
    }

    return 0;
}
