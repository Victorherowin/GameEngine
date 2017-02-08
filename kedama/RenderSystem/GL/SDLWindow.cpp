#include "SDLWindow.hpp"

#include <stdexcept>

#include "gl/glew.h"
#include "GLControl.hpp"

namespace Kedama
{
  SDLWindow::SDLWindow(GL::GLControl* control):m_control(control){}

  SDLWindow::~SDLWindow()
  {
    if(m_win)
      SDL_DestroyWindow(m_win);
  }

  void SDLWindow::Create(const string& title,int32_t w,int32_t h)
  {
    m_win=m_win=SDL_CreateWindow(title.c_str(),SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,w,h,SDL_WINDOW_SHOWN|SDL_WINDOW_ALLOW_HIGHDPI|SDL_WINDOW_OPENGL);
    if(!m_win)
      throw std::runtime_error("Create Window Failed");
    m_control->InitGL();
  }

  void SDLWindow::CreateFrom(void* handle)
  {
    m_win=m_win=SDL_CreateWindowFrom(handle);
    if(!m_win)
      throw std::runtime_error("Create Window Failed");
    m_control->InitGL();
  }

  void SDLWindow::SetTitle(const string& title)
  {
    SDL_SetWindowTitle(m_win,title.c_str());
  }

  void SDLWindow::SetSize(int32_t w,int32_t h)
  {
    SDL_SetWindowSize(m_win,w,h);
  }

  void SDLWindow::SetPosition(int32_t x,int32_t y)
  {
    SDL_SetWindowPosition(m_win,x,y);
  }

  void SDLWindow::SetFullscreen(bool flag)
  {
    if(flag)
      SDL_SetWindowFullscreen(m_win,SDL_WINDOW_FULLSCREEN);
    else
      SDL_SetWindowFullscreen(m_win,0);
  }

  const string SDLWindow::GetTitle()
  {
    return SDL_GetWindowTitle(m_win);
  }

  void SDLWindow::GetSize(int32_t* w,int32_t* h)
  {
    SDL_GetWindowSize(m_win,w,h);
  }

  void SDLWindow::GetPosition(int32_t* x,int32_t* y)
  {
    SDL_GetWindowPosition(m_win,x,y);
  }

  SDL_Window* SDLWindow::GetNativePtr()
  {
    return m_win;
  }
}
