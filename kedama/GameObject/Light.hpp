#ifndef LIGHT
#define LIGHT

#include "GameObject.hpp"

namespace Kedama {
  class Light:public GameObject
  {
  public:
    Light(const string& name);
    void SetColor(glm::u8vec3 rgb);


  protected:
  };

  class PointLight:public Light
  {
  public:

  private:
  };
}

#endif
