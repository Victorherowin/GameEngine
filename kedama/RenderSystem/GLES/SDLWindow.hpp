#ifndef SDLWINDOW
#define SDLWINDOW

#include <string>
#include <SDL2/SDL.h>

#include <IWindow.hpp>

namespace Kedama
{
	using std::string;
	class SDLWindow:public IWindow
	{
		public:
		SDLWindow();
		SDLWindow(const string& title,int w,int h);
		~SDLWindow();
		
		void Create(const string& title,int w,int h)override;
		void CreateFrom(void* handle)override;
		
		void SetTitle(const string& title)override;
		void SetSize(int w,int h)override;
		void SetPosition(int x,int y)override;
		void SetFullscreen(bool flag)override;
		
		const string GetTitle()override;
		void GetSize(int* w,int* h)override;
		void GetPosition(int* x,int* y)override;
		
		SDL_Window* GetPtr();
		
		private:
		SDL_Window* m_win;
	};
}

#endif
