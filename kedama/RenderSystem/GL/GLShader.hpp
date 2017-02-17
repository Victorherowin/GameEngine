#ifndef GLSHADER
#define GLSHADER

#include "../Shader.hpp"

#include "../../Include.hpp"

#include <string>
#include <GL/glew.h>

namespace Kedama
{
  namespace GL
  {
    using namespace std;
    //TODO:UBO的管理
    class GLShader:public Shader
    {
    public:
      GLShader(ShaderType type);
      ~GLShader();

      void SetSource(const string& src)override;
      //TODO 与Shader通信
      /*   void SetUniform(int loc,mat2& mat)override;
    void SetUniform(int loc,mat3& mat)override;
    void SetUniform(int loc,mat4& mat)override;
    void SetUniform(int loc,mat3x2& mat)override;
    void SetUniform(int loc,mat4x3& mat)override;
    void SetUniform(int loc,int32_t n)override;
    void SetUniform(int loc,int16_t n)override;
    void SetUniform(int loc,int8_t n)override;
    void SetUniform(int loc,uint32_t n)override;
    void SetUniform(int loc,uint16_t n)override;
    void SetUniform(int loc,uint8_t n)override;
    void SetUniform(int loc,float n)override;

    void SetUniform(int loc,vector<mat2>& mat)override;
    void SetUniform(int loc,vector<mat3>& mat)override;
    void SetUniform(int loc,vector<mat4>& mat)override;
    void SetUniform(int loc,vector<mat3x2>& mat)override;
    void SetUniform(int loc,vector<mat4x3>& mat)override;
    void SetUniform(int loc,vector<int32_t>& n)override;
    void SetUniform(int loc,vector<int16_t>& n)override;
    void SetUniform(int loc,vector<int8_t>& n)override;
    void SetUniform(int loc,vector<uint32_t>& n)override;
    void SetUniform(int loc,vector<uint16_t>& n)override;
    void SetUniform(int loc,vector<uint8_t>& n)override;
    void SetUniform(int loc,vector<float>& n)override;*/

      inline GLuint GetShader(){return m_shader;}
      inline GLenum GetGLTypeBit()
      {
        static GLenum table[]={GL_VERTEX_SHADER_BIT,GL_FRAGMENT_SHADER_BIT};
        return table[(int)m_type];
      }

    private:
      GLuint m_shader;
    };
  }
}

#endif
