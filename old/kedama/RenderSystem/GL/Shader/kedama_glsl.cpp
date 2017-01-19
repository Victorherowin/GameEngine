#include <string>

const std::string _kedama_glsl=
R"(#vertex_shader_begin
#version 330 core
layout (location = 0) in vec4 v_pos;
layout (location = 1) in vec4 v_normal;
layout (location = 2) in vec4 v_texcoord;
layout (location = 3) in vec4 v_tbn_quat;
#vertex_shader_end
)";
