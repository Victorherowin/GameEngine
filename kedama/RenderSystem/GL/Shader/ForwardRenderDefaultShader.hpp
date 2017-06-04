#include <string>

namespace Kedama
{
    namespace GLSL {
        const std::string default_vs_shader =
                R"(#version 450 core
layout(location=0)in vec4 v_pos;
layout(location=1)in vec4 v_uv;
layout(location=2)in vec4 v_normal;

out vec3 f_normal;
out vec2 f_uv;
out vec3 f_position;
	
layout(std140)uniform Model
{
	mat4 model_matrix[1000];
};

layout(std140)uniform Camera
{
	mat4 view_marix;
	mat4 projection_matrix;
	mat4 view_projection_matrix;
};

void VS_main()
{
	vec4 pos=view_projection_matrix*model_matrix[gl_InstanceID]*v_pos;
	f_position=pos.xyz;
	f_uv=v_uv.xy;
	f_normal=v_normal.xyz;
	gl_Position=pos;
}
	)";


        const std::string default_fs_shader =
                R"(#version 450 core
in vec3 f_position;
in vec3 f_normal;
in vec2 f_uv;

out vec4 out_color;
	
layout(std140)uniform Material
{
	bool use_texture;
    vec4 color;
    vec4 ambient;
    vec3 diffuse;
    vec4 specular;
    float shininess;
}material;

layout(std140)uniform Lights
{
    int type;
    float phi;
    vec4 direction;
    vec4 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
}lights;

uniform sampler2D texture0;

void FS_main()
{
	vec4 color=vec4(1.0,1.0,1.0,1.0);
	if(material.use_texture)
		color=texture2D(texture0,f_uv);
	else
		color=vec4(material.color.rgb,1.0);
	out_color=color;
}
	)";
    }
}
