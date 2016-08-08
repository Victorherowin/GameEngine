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
    Vertex(vec3(-1.0f,-1.0f,0.0f),vec2(1.0f,0.0f)),
    Vertex(vec3(1.0f,-1.0f,0.0f),vec2(1.0f,1.0f))
    });

vector<uint32> index({0,1,2});

int32_t main(int32_t argc,char** argv)
{
    RenderSystemFactoryManager::GetSingleton().RegisterFactory("GLRenderSystem",new Kedama::GLRenderSystemFactory());
    Engine engine("GLRenderSystem");
    RenderSystem* irs = engine.GetRenderSystem();
    SceneManager* sm=engine.GetSceneManager();
    IRenderSystemFactory* irsf=engine.GetRenderSystemFactory();
    IWindow* win=irs->GetWindow();
    win->SetTitle("ForwardRender Test");

    StaticModel* tri=new StaticModel("test node");
    sm->GetRoot().AddNode(tri);
    //go->

    IShaderPtr shader=irsf->CreateShader(shader_src);

    VertexBufferPtr vbo=irsf->CreateVertexBuffer();
    IIndexBufferPtr ibo=irsf->CreateIndexBuffer();

    SDL_Surface* t=IMG_Load(R"(C:\Users\MaoYu\Desktop\yande.re 361945 cameltoe hakamada_hinata loli pantsu ro-kyu-bu! thighhighs tinkle topless undressing.png)");
    SDL_Surface* tt=SDL_ConvertSurfaceFormat(t,SDL_PIXELFORMAT_ABGR8888,0);


    ITexture2DPtr tex=irsf->CreateTexture2D();
    tex->CreateCompressFromPixels(TextureCompressFormat::RGBA,TextureFormat::RGBA,0,tt->pixels,tt->w,tt->h);
    SDL_FreeSurface(t);
    SDL_FreeSurface(tt);

    vbo->SendVertices(vert,BufferUsage::StaticDraw);
    ibo->SendIndices(index);

    RenderStreamPtr rs=tri->GetRenderStream();
    uint32 mesh_id=rs->AddMeshBuffer(RenderStream::MeshBuffer(vbo,ibo));

    MaterialPtr material=Material::CreateMaterial();
    material->AddPass(nullptr,nullptr,shader);
    material->BindTexture(tex);

    rs->BindMaterial(mesh_id,material,0);
    rs->GetInstancingInfoRef(mesh_id).AddInstance(mat4());


    CameraPtr camera=Camera::CreateCamera("test_camera");
    int w,h;
    win->GetSize(&w,&h);
    camera->SetPerspective(45.0f,(float)w/(float)h,0.1f,1000.0f);
    camera->GetTansform().Move(vec3(0.0f,0.0f,10.0f));
    camera->LookAt(tri);

    irs->SetCamera(camera);

    SDL_Event ev;
    bool flag=false;
    vec3 direct=vec3(0.0f,0.0f,1.0f);
    while(!flag)
    {
      while(SDL_PollEvent(&ev))if(ev.type==SDL_QUIT)flag=true;
      irs->Clear();
      irs->Render(rs);
      irs->SwapBuffer();
      tri->GetTansform().Move(glm::vec3(0.0f,-0.05f,0.0f));
      rs->GetInstancingInfoRef(mesh_id).GetModelMatrix(0)=tri->GetTansform().GetWorldMatrix();
      //camera->LookDirect(direct=vec3(glm::rotate(glm::half_pi<float>()/45.0f,vec3(0.0f,1.0f,0.0f))*vec4(direct,0.0f)));
      this_thread::sleep_for(chrono::milliseconds(16));
    }
    return 0;
}
