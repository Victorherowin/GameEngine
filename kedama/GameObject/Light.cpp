#include "Light.hpp"
#include "../Engine.hpp"

#define UINT8_CONVERT_TO_FLOAT_VEC3(vec,rgb) vec.r = rgb.r / 255.0f;\
										 	 vec.g = rgb.g / 255.0f;\
											 vec.b = rgb.b / 255.0f;

namespace Kedama
{

  Light::Light(const string& name,LightType _type):GameObject(name),type(_type)
  {
	  m_native = Engine::GetSingletonPtr()->GetRendererFactory()->CraeteLightNative();
      AddUpdateListener("__postion_listener__", [this](Transform& t) {
		  this->m_native->UploadPosition(t.GetWorldPosition());
	  });
  }

  Light::~Light()
  {
	  delete m_native;
  }

  void Light::SetAmbient(glm::u8vec3 rgb)
  {
	  UINT8_CONVERT_TO_FLOAT_VEC3(ambient, rgb);
  }

  void Light::SetDiffuse(glm::u8vec3 rgb)
  {
	  UINT8_CONVERT_TO_FLOAT_VEC3(diffuse, rgb);
  }

  void Light::SetSpecular(glm::u8vec3 rgb)
  {
	  UINT8_CONVERT_TO_FLOAT_VEC3(specular, rgb);
  }

  PointLight::PointLight(const string &name):Light(name,LightType::PointLight)
  {

  }

  SpotLight::SpotLight(const string &name):Light(name,LightType::SpotLight)
  {

  }
}
