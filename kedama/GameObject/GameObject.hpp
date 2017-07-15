#ifndef GAMEOBJECT
#define GAMEOBJECT

#include <vector>

#include "Transform.hpp"
#include "../Include.hpp"
#include "../Define.hpp"

namespace Kedama
{
  using namespace std;

  class KEDAMA_API GameObject:public Transform
  {
  public:

    GameObject(const string& name="GameObject");
    virtual ~GameObject();

    inline const string& GetName()const
    {return m_name;}

    GameObject* GetChild(const string& name);

  private:
    string m_name;
  };
}

#endif
