#ifndef RENDERSYSTEM
#define RENDERSYSTEM

#include <string>
#include "../GameObject.hpp"
#include "ITexture2D.hpp"
#include "IShader.hpp"
#include "../IWindow.hpp"
#include "Mesh.hpp"
#include "RenderStream.hpp"
#include "../Camera.hpp"

#include "../Config.hpp"

namespace Kedama
{
    using std::string;

    class RenderSystem
    {
    public:
        virtual ~RenderSystem(){}

        void Render(RenderStreamPtr&);
        void UseDeferredRender(bool use);
        void SetCamera(CameraPtr camera);

        virtual void Init()=0;
        virtual void Quit()=0;
        virtual IWindow* GetWindow()=0;

        virtual void Clear()=0;
        virtual void Flush()=0;
        virtual void SwapBuffer()=0;
        virtual IShader* CreateShader(std::string shader_src)=0;

    protected:
        virtual void OnForwardRender(RenderStreamPtr& rsptr)=0;
        virtual void OnDeferredRender(RenderStreamPtr&){throw std::runtime_error(string("No Implement DeferredRender！"));}

        virtual const string GetShaderLanguage()=0;

    protected:
        CameraPtr m_main_camera=nullptr;
    private:
        bool m_use_deferred_render;
    };
}

#endif
