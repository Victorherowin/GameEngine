#include "GLLightNative.hpp"

#include <GL/glew.h>

namespace Kedama
{
	namespace GL
	{
		struct GLLight
		{
			LightType type;
			GLfloat phi;
			GLfloat padding[2];
			glm::vec4 direction;//w is padding
			glm::vec4 position;//w is padding
            glm::vec4 ambient;//w is padding
			glm::vec4 diffuse;//w is padding
			glm::vec4 specular;//w is padding
		};

		GLLightNative::GLLightNative()
		{
			glCreateBuffers(1,&m_ubo);
			glNamedBufferStorage(m_ubo, sizeof(GLLight), nullptr, GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);
			m_gl_light=(GLLight*)glMapNamedBufferRange(m_ubo, 0, sizeof(GLLight), GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);
		}

		GLLightNative::~GLLightNative()
		{
			glUnmapNamedBuffer(m_ubo);
			glDeleteBuffers(1,&m_ubo);
		}

		void GLLightNative::UploadColor(Light* light)
		{
			m_gl_light->ambient = glm::vec4(light->GetAmbient(),1.0f);
			m_gl_light->diffuse = glm::vec4(light->GetDiffuse(), 1.0f);
			m_gl_light->specular = glm::vec4(light->GetSpecular(), 1.0f);

			DirectionalLight* dl;
			SpotLight* sl;

			switch (light->GetType())
			{
			case LightType::DirectionalLight:
				dl = static_cast<DirectionalLight*>(light);
				m_gl_light->direction = glm::vec4(dl->GetDirection(),0.0f);
				break;

			case LightType::SpotLight:
				sl = static_cast<SpotLight*>(light);
				m_gl_light->phi = glm::cos(sl->GetAngle());
				m_gl_light->direction = vec4(sl->GetDirection(),0.0f);
			}
		}

		void GLLightNative::UploadPosition(const vec3& positon)
		{
			m_gl_light->position = vec4(positon,1.0f);
		}
	}
}
