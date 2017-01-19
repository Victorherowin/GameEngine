#ifndef SHADER
#define SHADER

#include "../Include.hpp"
#include "../Define.hpp"

namespace Kedama
{
  using namespace std;
  using namespace glm;

  class KEDAMA_API Shader
  {
    public:

    enum class ShaderType
    {
      VERTEX_SHADER,FRAGMENT_SHADER
    };

    protected:
    Shader(ShaderType type);

    public:

    virtual ~Shader(){}
    inline ShaderType GetType(){return m_type;}
    virtual void SetSource(const string& src)=0;
//TODO Uniform设置
/*    virtual void SetUniform(int loc,mat2& mat)=0;
    virtual void SetUniform(int loc,mat3& mat)=0;
    virtual void SetUniform(int loc,mat4& mat)=0;
    virtual void SetUniform(int loc,mat3x2& mat)=0;
    virtual void SetUniform(int loc,mat4x3& mat)=0;
    virtual void SetUniform(int loc,int32_t n)=0;
    virtual void SetUniform(int loc,int16_t n)=0;
    virtual void SetUniform(int loc,int8_t n)=0;
    virtual void SetUniform(int loc,uint32_t n)=0;
    virtual void SetUniform(int loc,uint16_t n)=0;
    virtual void SetUniform(int loc,uint8_t n)=0;
    virtual void SetUniform(int loc,float n)=0;

    virtual void SetUniform(int loc,vector<mat2>& mat)=0;
    virtual void SetUniform(int loc,vector<mat3>& mat)=0;
    virtual void SetUniform(int loc,vector<mat4>& mat)=0;
    virtual void SetUniform(int loc,vector<mat3x2>& mat)=0;
    virtual void SetUniform(int loc,vector<mat4x3>& mat)=0;
    virtual void SetUniform(int loc,vector<int32_t>& n)=0;
    virtual void SetUniform(int loc,vector<int16_t>& n)=0;
    virtual void SetUniform(int loc,vector<int8_t>& n)=0;
    virtual void SetUniform(int loc,vector<uint32_t>& n)=0;
    virtual void SetUniform(int loc,vector<uint16_t>& n)=0;
    virtual void SetUniform(int loc,vector<uint8_t>& n)=0;
    virtual void SetUniform(int loc,vector<float>& n)=0;*/

    protected:
    ShaderType m_type;
  };

}

#endif
