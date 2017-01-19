#include <string>

const std::string _default_shader_xml=
R"(<Shader>
    <Pass sequence="1">
    	<SubShader language="GLSL">
                #vertex_shader_begin
                #version 330 core
        	out vec3 f_normal;
            void main()
            {

            }
            #vertex_shader_end
            #fragment_shader_begin
        	void main()
        	{

        	}
        	#fragment_shader_end
    	</SubShader>
    </Pass>
</Shader>
)";
