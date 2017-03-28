#ifndef _H_GLLIGHTNATIVE
#define _H_GLLIGHTNATIVE

#include "../../Include.hpp"
#include "../../Define.hpp"
#include "../../GLMInclude.hpp"
#include "../../GameObject/Light.hpp"
#include <GL/glew.h>

namespace Kedama
{
	namespace GL
	{
		struct GLLight;

		class KEDAMA_API GLLightNative :public Light::INative
		{
		public:
			GLLightNative();
			~GLLightNative();
			void UploadColor(Light* light)override;
			void UploadPosition(const vec3& positon)override;
			inline GLuint GetUBO() { return m_ubo; }
		private:
			GLuint m_ubo=0;
			GLLight* m_gl_light = nullptr;
		};
	}
}

#endif
