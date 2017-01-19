#include <Engine.hpp>
#include <RenderSystem/RenderSystemFactoryManager.hpp>
#include <RenderSystem/GL/GLRenderSystemFactory.hpp>
#include <RenderSystem/IRenderSystemFactory.hpp>
#include <IWindow.hpp>
#include <Log.hpp>

#include <string>
#include <thread>
#include <chrono>

#include <GL/glew.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#undef main

using namespace  std;
using namespace Kedama;
using namespace Kedama::GL;

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


vector<uint32> index({0,1,2});
vector<uint32> floor_index({0,1,2,0,3,2});

int32_t main(int32_t argc,char** argv)
{
    RenderSystemFactoryManager::GetSingleton().RegisterFactory("GLRenderSystem",new GLRenderSystemFactory());
    Engine engine("GLRenderSystem");
    RenderSystem* irs = engine.GetRenderSystem();
    SceneManager* sm=engine.GetSceneManager();
    IRenderSystemFactory* irsf=engine.GetRenderSystemFactory();
    IWindow* win=irs->GetWindow();
    win->SetTitle("ForwardRender Test");

    return 0;
}
