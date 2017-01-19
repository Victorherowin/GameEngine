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
      const char* tmp=src.c_str();
      m_shader=glCreateShaderProgramv(__table[(int)m_type],1,&tmp);
    }
  }
}
