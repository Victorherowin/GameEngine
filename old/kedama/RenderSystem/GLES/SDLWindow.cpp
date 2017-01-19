#include "GLES/SDLWindow.hpp"

#include <stdexcept>

namespace Kedama
{
	SDLWindow::SDLWindow(const string& title,int w,int h)
	{
		Create(title,w,h);
	}
	
	SDLWindow::~SDLWindow()
	{
		if(m_win)
			SDL_DestroyWindow(m_win);
	}
	
	void SDLWindow::Create(const string& title,int w,int h)
	{
		m_win=m_win=SDL_CreateWindow(title.c_str(),SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,w,h,SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL);
		if(!m_win)
			throw std::runtime_error("Create Window Failed");
	}
	
	void SDLWindow::CreateFrom(void* handle)
	{
		m_win=m_win=SDL_CreateWindowFrom(handle);
		if(!m_win)
			throw std::runtime_error("Create Window Failed");
	}
	
	void SDLWindow::SetTitle(const string& title)
	{
		SDL_SetWindowTitle(m_win,title.c_str());
	}
	
	void SDLWindow::SetSize(int w,int h)
	{
		SDL_SetWindowSize(m_win,w,h);
	}
	
	void SDLWindow::SetPosition(int x,int y)
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
		return string(SDL_GetWindowTitle(m_win));
	}
	
	void SDLWindow::GetSize(int* w,int* h)
	{
		SDL_GetWindowSize(m_win,w,h);
	}
	
	void SDLWindow::GetPosition(int* x,int* y)
	{
		SDL_GetWindowPosition(m_win,x,y);
	}

	
	SDL_Window* SDLWindow::GetPtr()
	{
		return m_win;
	}
}