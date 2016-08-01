#ifndef GLSHADER
#define GLSHADER

#include "../IShader.hpp"

#include <string>
#include <GL/glew.h>

namespace Kedama
{
  using std::string;

  class GLShader:public IShader
  {
  public:
    GLShader(const string& vertex_shader,const string& fragment_shader);
    ~GLShader();
    void Create(const string& vertex_shader,const string& fragment_shader);

    GLuint GetShader();
  private:
    GLuint m_shader;
  };
}

#endif
