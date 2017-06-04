#include "Joint.hpp"

namespace Kedama
{
  Joint::Joint(const string& name):m_name(name)
  {
    AddUpdateListener("__bone_updater__",[this](Transform& t)
    {
      this->m_world_dq=dualquat_cast(mat3x4(t.GetWorldMatrix()));
    });
  }

  Joint::~Joint()
  {
  }
}
