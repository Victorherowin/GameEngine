#ifndef FORWARDRENDERPIPELINE
#define FORWARDRENDERPIPELINE

#include "IRenderPipeline.hpp"
#include "IRenderSystem.hpp"

namespace Kedama {
    class KEDAMA_LIB ForwardRenderPipeline:public IRenderPipeline
    {
    public:
	ForwardRenderPipeline()=default;
	ForwardRenderPipeline(IRenderSystem* irs);
	void Create(IRenderSystem* irs);

	void AddGameObject(GameObject* game_object)override;
	void RenderAll()override;
	void RenderTarget(IFrameBuffer* frame_buffer)override;
    private:
	IRenderSystem* m_render_system;
    };
}

#endif
