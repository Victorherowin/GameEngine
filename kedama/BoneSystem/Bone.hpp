#ifndef _H_BONE
#define _H_BONE

#include "../Define.hpp"
#include "../GLMInclude.hpp"
#include "../Include.hpp"

#include "../GameObject/Transform.hpp"

namespace Kedama
{
  using namespace glm;
  using namespace std;

  class KEDAMA_API Bone:public Transform
  {
  public:
    Bone(const string& name);
    ~Bone();

    inline dualquat GetWorldDualQuat(){return m_world_dq;}

  private:
    string m_name;
    //world space
    dualquat m_world_dq;
  };
}

#endif
