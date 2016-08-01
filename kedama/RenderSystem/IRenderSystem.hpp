#ifndef IRENDERSYSTEM
#define IRENDERSYSTEM

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

class IRenderSystem
{
public:
    virtual ~IRenderSystem(){}

    virtual void Init()=0;
    virtual void Quit()=0;
    virtual IWindow* GetWindow()=0;

    virtual void SetCamera(CameraPtr camera)=0;
    virtual void Clear()=0;
    virtual void Flush()=0;
    virtual void SwapBuffer()=0;
    virtual void OnRender(RenderStreamPtr)=0;

    virtual IShader* CreateShader(std::string shader_src)=0;
    virtual const string GetShaderLanguage()=0;

};
}

#endif
