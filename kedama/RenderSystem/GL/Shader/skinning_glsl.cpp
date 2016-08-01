#include <string>

const std::string _skinning_glsl=
R"(#vertex_shader_begin
#version 330 core
layout (location = 4) in ivec4 v_bone_index;
layout (location = 5) in vec4 v_bone_weight;
uniform mat4x3 v_bone_matrix[512];
uniform int v_bone_matrix_lenght;

uniform bool kedama_was_skinning=false;
uniform mat4 kedama_projection_matrix;
uniform mat4 kedama_model_view_matrix;
uniform mat3 kedama_normal_matrix;

mat3 quat2mat3(in vec4 quat)
{
	mat3 qmat;
	float xx=quat.x*quat.x;
	float yy=quat.y*quat.y;
	float zz=quat.z*quat.z;
	float xy=quat.x*quat.y;
	float wz=quat.w*quat.z;
	float xz=quat.x*quat.z;
	float wy=quat.w*quat.y;
	float yz=quat.y*quat.z;
	float wx=quat.w*quat.x;
	qmat[0][0]=1-2*yy-2*zz;qmat[0][1]=2*xy+2*wz;qmat[0][2]=2*xz-2*wz;
	qmat[1][0]=2*xy-2*wz;qmat[1][1]=1-2*xx-2*zz;qmat[1][2]=2*yz+2*wx;
	qmat[2][0]=2*xz+2*wy;qmat[2][1]=2*yz-2*wx;qmat[2][2]=1-2*xx-2*yy;
	return qmat;
}

void skinning(inout vec4 pos,inout vec4 normal)
{

}
#vertex_shader_end

)";