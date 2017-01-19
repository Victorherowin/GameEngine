#include "GLES/GLESRenderSystemFactory.hpp"
#include "GLES/GLESRenderSystem.hpp"

namespace Kedama
{
	IRenderSystem* GLESRenderSystemFactory::CreateRenderSystem()
	{
		IRenderSystem* irs=static_cast<IRenderSystem*>(new GLESRenderSystem());
		irs->Init();
		return irs;
	}
	
	void GLESRenderSystemFactory::DeleteRenderSystem(IRenderSystem* render_system)
	{
		render_system->Quit();
		delete render_system;
	}
	
}