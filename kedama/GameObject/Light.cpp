#include "Light.hpp"

namespace Kedama
{
  Light::Light(const string& name,LightType _type):GameObject(name),type(_type)
  {

  }

  PointLight::PointLight(const string &name):Light(name,LightType::PointLight)
  {

  }

  SpotLight::SpotLight(const string &name):Light(name,LightType::SpotLight)
  {

  }
}
