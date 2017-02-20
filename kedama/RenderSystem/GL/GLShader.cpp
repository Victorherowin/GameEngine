#include "GLShader.hpp"

#include <stdexcept>
#include <GL/glew.h>
#include "Shader/ShaderLib.hpp"

using namespace std;

namespace Kedama
{
  namespace GL
  {
    int GLShader::count=0;
    GLuint GLShader::FsShaderLibrary=0;
    GLuint GLShader::VsShaderLibrary=0;

    GLShader::GLShader()
    {
      if(count==0)
      {
        const char* tmp=VsShaderLibraryStr.c_str();
        GLint size=VsShaderLibraryStr.size();
        VsShaderLibrary=glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(VsShaderLibrary,1,&tmp,&size);
        glCompileShader(VsShaderLibrary);

        GLint status;
        glGetShaderiv(VsShaderLibrary,GL_COMPILE_STATUS,&status);

        if(status==GL_FALSE)
        {
          GLsizei log_size;
          glGetShaderiv(VsShaderLibrary,GL_INFO_LOG_LENGTH,&log_size);
          char* log=new char[log_size+1];
          glGetShaderInfoLog(VsShaderLibrary,log_size,&log_size,log);
          string log_str("----VertexShader----\n");
          log_str.append(log);
          delete[] log;
          throw runtime_error(log_str);
        }

        tmp=FsShaderLibraryStr.c_str();
        size=FsShaderLibraryStr.size();
        FsShaderLibrary=glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(FsShaderLibrary,1,&tmp,&size);
        glCompileShader(FsShaderLibrary);

        glGetShaderiv(FsShaderLibrary,GL_COMPILE_STATUS,&status);

        if(status==GL_FALSE)
        {
          GLsizei log_size;
          glGetShaderiv(FsShaderLibrary,GL_INFO_LOG_LENGTH,&log_size);
          char* log=new char[log_size+1];
          glGetShaderInfoLog(FsShaderLibrary,log_size,&log_size,log);
          string log_str("----FragmentShader----\n");
          log_str.append(log);
          delete[] log;
          throw runtime_error(log_str);
        }
        ++count;
      }
    }

    GLShader::~GLShader()
    {
      if(m_shader!=0)
        glDeleteProgram(m_shader);
      --count;
      if(count==0)
      {
        glDeleteShader(VsShaderLibrary);
        glDeleteShader(FsShaderLibrary);
      }
    }

    void GLShader::SetVertexShaderSource(const string &src)
    {
      string shader_str(src);

      const char* tmp=shader_str.c_str();
      GLint size=shader_str.size();
      m_vs=glCreateShader(GL_VERTEX_SHADER);
      glShaderSource(m_vs,1,&tmp,&size);
      glCompileShader(m_vs);

      GLint status;
      glGetShaderiv(m_vs,GL_COMPILE_STATUS,&status);

      if(status==GL_FALSE)
      {
        GLsizei log_size;
        glGetShaderiv(m_vs,GL_INFO_LOG_LENGTH,&log_size);
        char* log=new char[log_size+1];
        glGetShaderInfoLog(m_vs,log_size,&log_size,log);
        string log_str("----VertexShader----\n");
        log_str.append(log);
        delete[] log;
        throw runtime_error(log_str);
      }
    }

    void GLShader::SetFragmentShaderSource(const string &src)
    {
      string shader_str(src);

      const char* tmp=shader_str.c_str();
      GLint size=shader_str.size();
      m_fs=glCreateShader(GL_FRAGMENT_SHADER);
      glShaderSource(m_fs,1,&tmp,&size);
      glCompileShader(m_fs);

      GLint status;
      glGetShaderiv(m_fs,GL_COMPILE_STATUS,&status);

      if(status==GL_FALSE)
      {
        GLsizei log_size;
        glGetShaderiv(m_fs,GL_INFO_LOG_LENGTH,&log_size);
        char* log=new char[log_size+1];
        glGetShaderInfoLog(m_fs,log_size,&log_size,log);
        string log_str("----FragmentShader----\n");
        log_str.append(log);
        delete[] log;
        throw runtime_error(log_str);
      }
    }

    void GLShader::Compile()
    {
      if(m_shader!=0)
        glDeleteProgram(m_shader);
      m_shader=glCreateProgram();

      glAttachShader(m_shader,FsShaderLibrary);
      glAttachShader(m_shader,VsShaderLibrary);
      glAttachShader(m_shader,m_vs);
      glAttachShader(m_shader,m_fs);
      glLinkProgram(m_shader);

      GLint status=0;

      glGetProgramiv(m_shader,GL_LINK_STATUS,&status);
      if(status==GL_FALSE)
      {
        GLsizei log_size;
        glGetProgramiv(m_shader,GL_INFO_LOG_LENGTH,&log_size);
        char* log=new char[log_size+1];
        glGetProgramInfoLog(m_shader,log_size,&log_size,log);
        string log_str("-----Link----\n");
        log_str.append(log);
        delete[] log;
        throw runtime_error(log_str);
      }

      glDeleteShader(m_fs);
      glDeleteShader(m_vs);
    }
  }
}
