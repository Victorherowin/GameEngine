#ifndef LIGHT
#define LIGHT

#include "GameObject.hpp"
#include "../RenderSystem/Material.hpp"

namespace Kedama {
  enum class LightType
  {
    DirectionalLight=0,PointLight=1,SpotLight=2
  };

  class Light:public GameObject
  {
  protected:
    Light(const string& name,LightType type);
  public:
    inline LightType GetType(){return type;}

    void SetColor(glm::u8vec3 rgb);
    inline glm::vec4 GetColor(){return color;}
  protected:
    LightType type;
    glm::vec4 color;
  };

  class DirectionalLight:public Light
  {
  public:
    DirectionalLight(const string& name);
  };

  class PointLight:public Light
  {
  public:
    PointLight(const string& name);
  private:
  };

  class SpotLight:public Light
  {
  public:
    SpotLight(const string& name);
    inline void SetRadius(float radius){m_radius=radius;}
    inline float GetRadius(){return m_radius;}

  private:
    float m_radius=1.0f;
  };
}

#endif
