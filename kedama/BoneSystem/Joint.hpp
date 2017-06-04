#ifndef _H_JOINT
#define _H_JOINT

#include "../Define.hpp"
#include "../GLMInclude.hpp"
#include "../Include.hpp"

#include "../GameObject/Transform.hpp"

namespace Kedama
{
  using namespace glm;
  using namespace std;

  class KEDAMA_API Joint:public Transform
  {
  public:
    Joint(const string& name);
    ~Joint();

    inline dualquat GetWorldDualQuat(){return m_world_dq;}

  private:
    string m_name;
    //world space
    dualquat m_world_dq;
  };
}

#endif
