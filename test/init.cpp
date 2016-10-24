#include <Engine.hpp>
#include <RenderSystem/RenderSystemFactoryManager.hpp>
#include <RenderSystem/GL/GLRenderSystemFactory.hpp>
#include <RenderSystem/IRenderSystemFactory.hpp>
#include <RenderSystem/RenderStream.hpp>
#include <IWindow.hpp>
#include <Log.hpp>

#include <string>
#include <thread>
#include <chrono>

#include <GL/glew.h>
#include <RenderSystem/Vertex.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#undef main

using namespace  std;
using namespace Kedama;

string shader_src=
R"(#vertex_shader_begin
   #version 430 core
   uniform mat4 kedama_view_matrix;
   uniform mat4 kedama_projection_matrix;
   uniform mat4 kedama_model_matrix;

   layout(location = 0)in vec4 pos;
   layout(location = 1)in vec4 uv;
   out vec2 f_uv;
   void main()
   {
    gl_Position=kedama_projection_matrix*kedama_view_matrix*kedama_model_matrix*pos;
    f_uv=uv.xy;
   }
   #vertex_shader_end

   #fragment_shader_begin
   #version 430 core
   in vec2 f_uv;
   layout(location = 0)uniform sampler2D kedama_tex;
   void main()
   {
     gl_FragColor=/*vec4(f_uv,0.0,1.0);*/texture(kedama_tex,f_uv);
   }
   #fragment_shader_end)";

vector<Vertex> vert({
    Vertex(vec3(0.0f,1.0f,0.0f),vec2(0.5f,0.0f)),
    Vertex(vec3(-1.0f,-1.0f,0.0f),vec2(0.0f,1.0f)),
    Vertex(vec3(1.0f,-1.0f,0.0f),vec2(1.0f,1.0f))
    });

vector<Vertex> floor_vert({
  Vertex(vec3(-1.0f,1.0f,0.0f),vec2(0.0f,0.0f)),
  Vertex(vec3(1.0f,1.0f,0.0f),vec2(1.0f,0.0f)),
  Vertex(vec3(1.0f,-1.0f,0.0f),vec2(1.0f,1.0f)),
  Vertex(vec3(-1.0f,-1.0f,0.0f),vec2(0.0f,1.0f)),
  });

vector<uint32> index({0,1,2});
vector<uint32> floor_index({0,1,2,0,3,2});

int32_t main(int32_t argc,char** argv)
{
    RenderSystemFactoryManager::GetSingleton().RegisterFactory("GLRenderSystem",new Kedama::GLRenderSystemFactory());
    Engine engine("GLRenderSystem");
    RenderSystem* irs = engine.GetRenderSystem();
    SceneManager* sm=engine.GetSceneManager();
    IRenderSystemFactory* irsf=engine.GetRenderSystemFactory();
    IWindow* win=irs->GetWindow();
    win->SetTitle("ForwardRender Test");

    IShaderPtr shader=irsf->CreateShader(shader_src);

    VertexBufferPtr vbo=irsf->CreateVertexBuffer();
    IIndexBufferPtr ibo=irsf->CreateIndexBuffer();

    VertexBufferPtr floor_vbo=irsf->CreateVertexBuffer();
    IIndexBufferPtr floor_ibo=irsf->CreateIndexBuffer();

    SDL_Surface* t=IMG_Load(R"(F:\pixiv\[Nikennosekai] Prinz Eugen (1).jpeg)");
    SDL_Surface* tt=SDL_ConvertSurfaceFormat(t,SDL_PIXELFORMAT_ABGR8888,0);


    ITexture2DPtr tex=irsf->CreateTexture2D();
    tex->CreateCompressFromPixels(TextureCompressFormat::RGBA,TextureFormat::RGBA,0,tt->pixels,tt->w,tt->h);
    SDL_FreeSurface(t);
    SDL_FreeSurface(tt);

    vbo->SendVertices(vert,BufferUsage::StaticDraw);
    ibo->SendIndices(index);

    floor_vbo->SendVertices(floor_vert,BufferUsage::StaticDraw);
    floor_ibo->SendIndices(floor_index);

    MaterialPtr material=Material::CreateMaterial();
    material->AddPass(nullptr,nullptr,shader);
    material->BindTexture(tex);

    BaseModelPtr tri=BaseModel::CreateBaseModel("test node");
    sm->GetRoot().AddNode(tri);
    tri->AddMesh(MeshBuffer(vbo,ibo),material);

    BaseModelPtr tri2=BaseModel::CreateBaseModel("test node2");
    tri->AddNode(tri2);
    tri2->AddMesh(MeshBuffer(vbo,ibo),material);
    tri2->GetTansform().Rotate(glm::vec3(0.0f,1.0f,0.0f),glm::pi<float>()/3.0f);

    BaseModelPtr tri3=BaseModel::CreateBaseModel("test node3");
    tri2->AddNode(tri3);
    tri3->AddMesh(MeshBuffer(vbo,ibo),material);
    tri3->GetTansform().Rotate(glm::vec3(0.0f,1.0f,0.0f),glm::pi<float>()/3.0f*4.0f);

    BaseModelPtr floor=BaseModel::CreateBaseModel("floor");
    floor->AddMesh(MeshBuffer(floor_vbo,floor_ibo),material);
    floor->GetTansform().SetScale(vec3(100.0f,100.0f,100.0f));
    floor->GetTansform().Rotate(vec3(1.0f,0.0f,0.0f),glm::half_pi<float>());
    sm->GetRoot().AddNode(floor);

    int w,h;
    win->GetSize(&w,&h);

    CameraPtr camera=Camera::CreateCamera("test_camera");
    Viewport vp;
    vp.SetPerspective(45.0f,(float)w/(float)h,0.1f,1000.0f);
    irs->SetViewport(&vp);

    camera->GetTansform().Move(vec3(1.0f,1.8f,10.0f));
    camera->LookAt(tri);

    irs->SetCamera(camera);

    SDL_Event ev;
    bool flag=false;

    RenderStreamPtr rs=Engine::GetSingleton().GetRenderSystemFactory()->CreateRenderStream();

    while(!flag)
    {
      while(SDL_PollEvent(&ev))if(ev.type==SDL_QUIT)flag=true;
      irs->Clear();
      irs->Render(rs);
      irs->Render(rs);
      irs->Render(rs);
      irs->Render(rs);
      irs->SwapBuffer();
      tri->GetTansform().Rotate(vec3(0.0,1.0,0.0),glm::pi<float>()/180.0f);
      tri->GetTansform().Move(glm::vec3(0.0f,0.00f,0.05f));
      //camera->LookDirect(direct=vec3(glm::rotate(glm::half_pi<float>()/45.0f,vec3(0.0f,1.0f,0.0f))*vec4(direct,0.0f)));
      this_thread::sleep_for(chrono::milliseconds(16));
    }

    return 0;
}
