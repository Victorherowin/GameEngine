#ifndef ISHADER
#define ISHADER

#include "../Define.hpp"

namespace Kedama
{
  using namespace std;

  DEFINE_SHARED_PTR(IShader)

  class IShader
  {
    public:
    enum class ValueType
    {
      INT,UINT,FLOAT
    };

    enum class VectorType
    {
      NUMBER,VEC2,VEC3,VEC4
    };

    enum class MatrixType
    {
      MAT2,MAT3,MAT4,MAT2x3,MAT3x2,MAT2x4,MAT4x2,MAT3x4,MAT4x3
    };

    public:
    virtual ~IShader(){}
    virtual void BindUniform(ValueType type,VectorType vtype,uint32_t count,const void* data,const string& name)=0;
    virtual void BindUniformMatrix(MatrixType type,uint32_t count,const void* data,const string& name)=0;
  };

}

#endif
