#ifndef GLSHADER
#define GLSHADER

#include "../IShader.hpp"

#include <string>
#include <GL/glew.h>

namespace Kedama
{
  DEFINE_SHARED_PTR(GLShader)

  using std::string;

  class GLShader:public IShader
  {
  public:
    GLShader(const string& vertex_shader,const string& fragment_shader);
    ~GLShader();
    void Create(const string& vertex_shader,const string& fragment_shader);

    void BindUniform(ValueType type,VectorType vtype,uint32_t count,const void* data,const string& name)override;
    void BindUniformMatrix(MatrixType type,uint32_t count, const void* data,const string& name)override;

    void Use();
    inline GLuint GetShader(){return m_shader;}
  private:
    struct UniformInfo
    {
      int type;
      ValueType value_type;
      MatrixType matrix_type;
      uint32_t count;
      GLuint location;
      void* data;
    };

    GLuint m_shader;
    map<string,UniformInfo> m_uniform_info_map;
  };
}

#endif
