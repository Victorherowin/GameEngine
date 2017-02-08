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

    protected:
    ShaderType m_type;
  };

}

#endif
