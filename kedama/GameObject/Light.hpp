#ifndef LIGHT
#define LIGHT

#include "../Define.hpp"
#include "GameObject.hpp"
#include "../RenderSystem/Material.hpp"

namespace Kedama {
	enum class LightType :int32_t
	{
		DirectionalLight = 0, PointLight = 1, SpotLight = 2
	};

	class KEDAMA_API Light :public GameObject
	{
	protected:
		Light(const string& name, LightType type);
	public:
		~Light();
		class INative;
		inline INative* GetNative() { return m_native; }

		inline LightType GetType() { return type; }

		void SetAmbient(glm::u8vec3 rgb);
		void SetDiffuse(glm::u8vec3 rgb);
		void SetSpecular(glm::u8vec3 rgb);

		inline glm::vec3 GetAmbient() { return ambient; }
		inline glm::vec3 GetDiffuse() { return diffuse; }
		inline glm::vec3 GetSpecular() { return specular; }
	protected:

	protected:
		LightType type;
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;

		INative* m_native;
	};

	class KEDAMA_API Light::INative
	{
	public:
		virtual ~INative() {}
		virtual void UploadColor(Light*) = 0;
		virtual void UploadPosition(const vec3& positon) = 0;
	};

	class KEDAMA_API DirectionalLight :public Light
	{
	public:
		DirectionalLight(const string& name);

		inline void SetDirection(vec3 direction) { m_direction = direction; }
		inline vec3 GetDirection() { return m_direction; }
	private:
		vec3 m_direction = vec3(0.5f, -0.5f, 0.5f);
	};

	class KEDAMA_API PointLight :public Light
	{
	public:
		PointLight(const string& name);
	private:
	};

	class KEDAMA_API SpotLight :public Light
	{
	public:
		SpotLight(const string& name);
		inline void SetAngle(float phi) { m_phi = phi; }
		inline float GetAngle() { return m_phi; }

		inline void SetDirection(vec3 direction) { m_direction = direction; }
		inline vec3 GetDirection() { return m_direction; }

	private:
		vec3 m_direction = vec3(0.0f, 0.0f, 0.0f);
		float m_phi = glm::radians(12.5f);
	};
}

#endif
