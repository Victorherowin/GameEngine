#ifndef SHADER
#define SHADER

#include "../../Include.hpp"
#include "../../GLMInclude.hpp"
#include "../../Define.hpp"

namespace Kedama
{
  using namespace std;
  using namespace glm;

  class IShader
  {
    public:
    virtual ~IShader(){}
    virtual void SetVertexShaderSource(const string& src)=0;
    virtual void SetFragmentShaderSource(const string& src)=0;
    virtual void Compile()=0;
  };

}

#endif
