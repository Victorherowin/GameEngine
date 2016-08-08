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
    for(auto& info:m_uniform_info_map)
    {
      operator delete(info.second.data);
    }
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

  void GLShader::BindUniform(ValueType type,VectorType vtype, uint32_t count, const void *usr_data, const string &name)
  {
    auto it=m_uniform_info_map.find(name);
    if(it==m_uniform_info_map.end())
    {
      operator delete(it->second.data);
    }
    void* data=operator new(4*((int)vtype+1)*count);
    memcpy(data,usr_data,4*((int)vtype+1)*count);

    glUseProgram(m_shader);
    GLint location=glGetUniformLocation(m_shader,name.c_str());
    glUseProgram(0);

    UniformInfo uni;
    uni.type=0;
    uni.value_type=type;
    uni.count=count;
    uni.location=location;
    uni.data=data;
    m_uniform_info_map[name]=uni;
  }

  void GLShader::BindUniformMatrix(MatrixType type, uint32_t count, const void *usr_data, const string &name)
  {
    static int __byte_table[]={4,9,16,6,6,8,8,12,12};

    auto it=m_uniform_info_map.find(name);
    if(it==m_uniform_info_map.end())
    {
      operator delete(it->second.data);
    }
    void* data=operator new(4*__byte_table[(int)type]*count);
    memcpy(data,usr_data,4*__byte_table[(int)type]*count);

    glUseProgram(m_shader);
    GLint location=glGetUniformLocation(m_shader,name.c_str());
    glUseProgram(0);

    UniformInfo uni;
    uni.type=1;
    uni.matrix_type=type;
    uni.count=count;
    uni.location=location;
    uni.data=data;
    m_uniform_info_map[name]=uni;
  }

  void GLShader::Use()
  {
    typedef void (*UniformFuncPtrINT)(GLint,GLsizei,const GLint*)__attribute__((stdcall));
    typedef void (*UniformFuncPtrUINT)(GLint,GLsizei,const GLuint*)__attribute__((stdcall));
    typedef void (*UniformFuncPtrFLOAT)(GLint,GLsizei,const GLfloat*)__attribute__((stdcall));
    typedef void (*UniformFuncPtrMatrix)(GLint,GLsizei,GLboolean,const GLfloat*)__attribute__((stdcall));
    static UniformFuncPtrFLOAT __unformfunc_float_table[]={glUniform1fv,glUniform2fv,glUniform3fv,glUniform4fv};
    static UniformFuncPtrUINT __unformfunc_uint_table[]={glUniform1uiv,glUniform2uiv,glUniform3uiv,glUniform4uiv};
    static UniformFuncPtrINT __unformfunc_int_table[]={glUniform1iv,glUniform2iv,glUniform3iv,glUniform4iv};
    static UniformFuncPtrMatrix __unformfunc_matrix_table[]={glUniformMatrix2fv,glUniformMatrix3fv,glUniformMatrix4fv,
                                                         glUniformMatrix2x3fv,glUniformMatrix3x2fv,
                                                         glUniformMatrix2x4fv,glUniformMatrix4x2fv,
                                                         glUniformMatrix3x4fv,glUniformMatrix4x3fv};
    for(auto& it:m_uniform_info_map)
    {
      if(it.second.type==0)
      {
        if(it.second.value_type==ValueType::INT)
        {
          __unformfunc_int_table[(int)it.second.value_type](it.second.location,it.second.count,(const GLint*)it.second.data);
        }

        if(it.second.value_type==ValueType::UINT)
        {
          __unformfunc_uint_table[(int)it.second.value_type](it.second.location,it.second.count,(const GLuint*)it.second.data);
        }

        if(it.second.value_type==ValueType::FLOAT)
        {
          __unformfunc_float_table[(int)it.second.value_type](it.second.location,it.second.count,(const GLfloat*)it.second.data);
        }
      }
      else
      {
        __unformfunc_matrix_table[(int)it.second.matrix_type](it.second.location,it.second.count,GL_FALSE,(const GLfloat*)it.second.data);
      }
    }
  }

  void GLShader::SetViewMatrix(const glm::mat4 &view)
  {
    if(m_view_matrix_loc==std::numeric_limits<GLint>::max())
      m_view_matrix_loc=glGetUniformLocation(m_shader,"kedama_view_matrix");
    if(m_view_matrix_loc!=std::numeric_limits<GLint>::max())
      glUniformMatrix4fv(m_view_matrix_loc,1,GL_FALSE,glm::value_ptr(view));
  }

  void GLShader::SetProjectionMatrix(const glm::mat4 &projection)
  {
    if(m_projection_matrix_loc==std::numeric_limits<GLint>::max())
      m_projection_matrix_loc=glGetUniformLocation(m_shader,"kedama_projection_matrix");
    if(m_projection_matrix_loc!=std::numeric_limits<GLint>::max())
      glUniformMatrix4fv(m_projection_matrix_loc,1,GL_FALSE,glm::value_ptr(projection));
  }

  void GLShader::SetModelMatrix(const glm::mat4 &model)
  {
    if(m_model_matrix_loc==std::numeric_limits<GLint>::max())
      m_model_matrix_loc=glGetUniformLocation(m_shader,"kedama_model_matrix");
    if(m_model_matrix_loc!=std::numeric_limits<GLint>::max())
      glUniformMatrix4fv(m_model_matrix_loc,1,GL_FALSE,glm::value_ptr(model));
  }
}
