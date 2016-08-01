#ifndef GLESRENDERSYSTEMFACTORY
#define GLESRENDERSYSTEMFACTORY

#include "../IRenderSystemFactory.hpp"

namespace Kedama
{
	class GLESRenderSystemFactory:public IRenderSystemFactory
	{
		public:
		IRenderSystem* CreateRenderSystem()override;
		void DeleteRenderSystem(IRenderSystem*)override;
	};
}

#endif