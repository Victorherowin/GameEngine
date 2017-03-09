#ifndef SDLWINDOW
#define SDLWINDOW

#include <string>
#include <SDL.h>

#include "GLRenderSystemClass.hpp"
#include "../Interface/IWindow.hpp"

#undef main

namespace Kedama
{
  class SDLWindow:public IWindow
  {
  public:
    SDLWindow(GL::GLControl* control);
    ~SDLWindow();

    void Create(const string& title,int32_t w,int32_t h)override;
    void CreateFrom(void* handle)override;

    void SetTitle(const string& title)override;
    void SetSize(int32_t w,int32_t h)override;
    void SetPosition(int32_t x,int32_t y)override;
    void SetFullscreen(bool flag)override;

    const string GetTitle()override;
    void GetSize(int32_t* w,int32_t* h)override;
    void GetPosition(int32_t* x,int32_t* y)override;

    SDL_Window* GetNativePtr();

  private:
    SDL_Window* m_win;
    GL::GLControl* m_control;
  };
}

#endif
