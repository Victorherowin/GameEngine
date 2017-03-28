#ifndef GLSHADER
#define GLSHADER

#include "../Interface/IShader.hpp"

#include "../../Include.hpp"

#include <string>
#include <GL/glew.h>

#define MODEL_BINDING 0
#define CAMERA_BINDING 1
#define LIGHTS_BINDING 2
#define MATERIAL_BINDING 3

namespace Kedama
{
  namespace GL
  {
    using namespace std;
    class GLShader:public IShader
    {
    public:
      GLShader();
      ~GLShader();

      void SetVertexShaderSource(const string& src)override;
      void SetFragmentShaderSource(const string& src)override;
      void Compile()override;
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

    private:
      GLuint m_vs=0;
      GLuint m_fs=0;
      GLuint m_shader=0;

      static int count;
      static GLuint FsShaderLibrary;
      static GLuint VsShaderLibrary;
    };
  }
}

#endif
