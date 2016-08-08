#include "Vertex.hpp"

namespace Kedama
{
    Vertex::Vertex(const vec3& position,const vec2& uv,const vec3& normal,const mat3& tbn,
                   const u16vec4& bone_index,const vec4& weight):
      m_position(position),m_normal(normal),m_uv(uv),m_tbn_quat(glm::quat_cast(tbn)),
      m_bone_index(bone_index),m_weight(weight){}


}
