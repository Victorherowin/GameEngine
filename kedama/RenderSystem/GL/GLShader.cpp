#include "GLShader.hpp"

#include <stdexcept>
#include <GL/glew.h>

using namespace std;

namespace Kedama
{
  GLShader::GLShader(const string &vertex_shader, const string &fragment_shader)
  {
    m_shader=glCreateProgram();
    Create(vertex_shader,fragment_shader);
  }

  GLShader::~GLShader()
  {
    if(m_shader!=0)
      glDeleteProgram(m_shader);
  }

  void GLShader::Create(const string &vertex_shader, const string &fragment_shader)
  {
    GLuint vert_obj,frag_obj;
    GLint compile_status=GL_FALSE;
    vert_obj=glCreateShader(GL_VERTEX_SHADER);
    frag_obj=glCreateShader(GL_FRAGMENT_SHADER);
    const char* tmp_str=vertex_shader.c_str();
    GLint src_len=vertex_shader.size();
    glShaderSource(vert_obj,1,&tmp_str,&src_len);
    glCompileShader(vert_obj);
    glGetShaderiv(vert_obj,GL_COMPILE_STATUS,&compile_status);
    if(compile_status==GL_FALSE)
      {
        int32_t log_lenght=0;
        glGetShaderiv(vert_obj,GL_INFO_LOG_LENGTH,&log_lenght);
        std::string log;
        char *tmp=new char[log_lenght];
        glGetShaderInfoLog(vert_obj,log_lenght,&log_lenght,tmp);
        log.append(tmp,log_lenght);
        delete[] tmp;
        glDeleteShader(vert_obj);
        throw runtime_error(string("VertexShader:\n")+log);
      }

    tmp_str=fragment_shader.c_str();
    src_len=fragment_shader.size();
    glShaderSource(frag_obj,1,&tmp_str,&src_len);
    glCompileShader(frag_obj);
    glGetShaderiv(frag_obj,GL_COMPILE_STATUS,&compile_status);
    if(compile_status==GL_FALSE)
      {
        int32_t log_lenght=0;
        glGetShaderiv(frag_obj,GL_INFO_LOG_LENGTH,&log_lenght);
        std::string log;
        char *tmp=new char[log_lenght];
        glGetShaderInfoLog(frag_obj,log_lenght,&log_lenght,tmp);
        log.append(tmp,log_lenght);
        delete[] tmp;
        glDeleteShader(frag_obj);
        throw runtime_error(string("FragmentShader:\n")+log);
      }

    GLint link_status=GL_FALSE;
    glAttachShader(m_shader,vert_obj);
    glAttachShader(m_shader,frag_obj);
    glLinkProgram(m_shader);

    glGetProgramiv(m_shader,GL_LINK_STATUS,&link_status);
    if(link_status==GL_FALSE)
      {
        int32_t log_lenght=0;
        glGetProgramiv(frag_obj,GL_INFO_LOG_LENGTH,&log_lenght);
        std::string log;
        char *tmp=new char[log_lenght];
        glGetProgramInfoLog(m_shader,log_lenght,&log_lenght,tmp);
        log.append(tmp,log_lenght);
        delete[] tmp;
        throw runtime_error(string("Shader Link Failed\n")+log);
      }
    glDeleteShader(vert_obj);
    glDeleteShader(frag_obj);
  }

  GLuint GLShader::GetShader()
  {
    return m_shader;
  }
}
