#ifndef GLESRENDERSYSTEM
#define GLESRENDERSYSTEM

#include "../IRenderSystem.hpp"
#include "SDLWindow.hpp"

namespace Kedama
{
	class GLESRenderSystem:public IRenderSystem
	{
		public:		
		void Init()override;
		void Quit()override;
		
		void Clear()override;
		void Flush()override;
		void SwapBuffer()override;
		
		void DrawRect(glm::vec2 pos1,glm::vec2 pos2,glm::vec4 color)override;
		void DrawGameObject(GameObject*)override;
		
		SDLWindow& GetWindow();
		
		private:
		SDLWindow m_win;
		SDL_GLContext m_gl;
	};
}

#endif