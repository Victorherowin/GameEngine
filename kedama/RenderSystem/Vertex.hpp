#ifndef VERTEX
#define VERTEX

#include "../Config.hpp"

namespace Kedama
{
    using namespace glm;
    class KEDAMA_API Vertex
    {
    public:
	inline void SetPositon(vec3 position){m_position=position;}
	inline void SetNormal(vec3 normal){m_normal=normalize(normal);}
	inline void SetTextureCoord(vec2 uv){m_uv=uv;}
	inline void SetWeight(int i,uint16 bone_index,float weight){m_bone_index[i]=bone_index;m_weight[i]=weight;}
/*	inline void SetTBN(vec3 tangent,vec3 noraml,vec3 bitangent){
	    m_tbn_quat.w=sqrt(tangent.x*noraml.y*bitangent.z+1);
	    m_tbn_quat.x=(noraml.z-bitangent.z)/4*m_tbn_quat.w;
	    m_tbn_quat.y=(bitangent.x-tangent.z)/4*m_tbn_quat.w;
	    m_tbn_quat.z=(tangent.y-noraml.x)/4*m_tbn_quat.w;
	}*///暂不实现切线空间

	inline vec3 GetPositon(){return m_position;}
	inline vec3 GetNormal(){return m_normal;}
	inline vec2 GetTextureCoord(){return m_uv;}
	inline quat GetTBNQuaternion(){return m_tbn_quat;}
	inline void GetBoneIndexAndWeight(uint16* bone_inedx,float* weight)
	{
		memcpy(bone_inedx,m_bone_index,sizeof(uint16)*4);
		memcpy(weight,&m_weight[0],sizeof(float)*4);
	}

    private:
	vec3 m_position;
	vec3 m_normal;
	vec2 m_uv;
	quat m_tbn_quat;
	uint16 m_bone_index[4];
	vec4 m_weight;
    };
}

#endif
