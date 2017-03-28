#include "Bone.hpp"

namespace Kedama
{
  Bone::Bone(const string& name):m_name(name)
  {
    AddUpdateListener("__bone_updater__",[this](Transform& t)
    {
      this->m_world_dq=dualquat_cast(mat3x4(t.GetWorldMatrix()));
    });
  }

  Bone::~Bone()
  {
  }
}
