#ifndef VERTEX
#define VERTEX

#include "../Config.hpp"

namespace Kedama
{
    using namespace glm;
    class KEDAMA_API Vertex
    {
    public:
        Vertex(const vec3& position,const vec2& uv=vec2(),const vec3& normal=vec3(),
               const mat3& tbn=mat3(),const u16vec4& bone_index=u16vec4(),
               const vec4& weight=vec4());

        inline void SetPositon(const vec3& position){m_position=position;}
        inline void SetNormal(const vec3& normal){m_normal=normalize(normal);}
        inline void SetTextureCoord(const vec2& uv){m_uv=uv;}
        inline void SetWeight(const u16vec4& bone_index,vec4 weight){m_bone_index=bone_index;m_weight=weight;}
        inline void SetTBN(const mat3& tbn){m_tbn_quat=glm::quat_cast(tbn);}

        inline vec3& GetPositon(){return m_position;}
        inline vec3& GetNormal(){return m_normal;}
        inline vec2& GetTextureCoord(){return m_uv;}
        inline quat& GetTBNQuaternion(){return m_tbn_quat;}
        inline u16vec4& GetBoneIndex(){return m_bone_index;}
        inline vec4& GetWeight(){return m_weight;}

    private:
	vec3 m_position;
        vec2 m_uv;
	vec3 m_normal;
	quat m_tbn_quat;
        u16vec4 m_bone_index;
	vec4 m_weight;
    };
}

#endif
