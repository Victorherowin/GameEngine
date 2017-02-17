#include "GLShader.hpp"

#include <stdexcept>
#include <GL/glew.h>

using namespace std;

namespace Kedama
{
  namespace GL
  {

    GLShader::GLShader(ShaderType type):Shader(type)
    {
    }

    GLShader::~GLShader()
    {
      if(m_shader!=0)
        glDeleteProgram(m_shader);
    }

    void GLShader::SetSource(const string &src)
    {
      static GLenum __table[]={GL_VERTEX_SHADER,GL_FRAGMENT_SHADER};
      static string __table_str[]={"VertexShader","FragmentShader"};
      string shader_str(src);
      if(m_type==Shader::ShaderType::VERTEX_SHADER)
      {
        auto it=shader_str.find("#version 450 core");
        if(it==string::npos)throw runtime_error("required \"#version 450 core\"");
        while(shader_str[it++]!='\n'){}
        shader_str.insert(it,"out gl_PerVertex{vec4 gl_Position;float gl_PointSize;float gl_ClipDistance[];};\n");
      }
      const char* tmp=shader_str.c_str();
      m_shader=glCreateShaderProgramv(__table[(int)m_type],1,&tmp);

      GLint link_status;
      glGetProgramiv(m_shader,GL_LINK_STATUS,&link_status);
      if(link_status==GL_FALSE)
      {
        GLsizei log_size;
        glGetProgramiv(m_shader,GL_INFO_LOG_LENGTH,&log_size);
        char* log=new char[log_size+1];
        glGetProgramInfoLog(m_shader,log_size,&log_size,log);
        string log_str;
        log_str+=__table_str[(int)m_type]+"\n";
        log_str.append(log);
        delete[] log;
        throw runtime_error(log_str);
      }
    }
  }
}
