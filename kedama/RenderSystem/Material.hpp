/*!
  \file MAterial.hpp
  \brief 材质类

  \author KedamaOvO
  \date 2017.02.01
*/

#ifndef MATERIAL
#define MATERIAL

#include "Interface/ITexture2D.hpp"
#include "../Include.hpp"
#include "../Define.hpp"
#include "Shader.hpp"

namespace Kedama
{
  using namespace glm;

  enum class DrawMode
  {
    LINES,NORMAL
  };

  struct KEDAMA_API Pass
  {
    //TODO:其他渲染设置
    DrawMode draw_mode=DrawMode::NORMAL;
    Shader* vertex_shader;
    Shader* fragment_shader;
  };

  class KEDAMA_API Material
  {
  public:
    class INative;
    struct Value;

  public:
    Material();
    ~Material();

    void SetVector3(const string& property,const vec3& vec);
    void SetVector4(const string& property,const vec4& vec);
    void SetFloat(const string& property,float _float);
    void SetInt(const string& property,int _int);
    void SetMatrix(const string& property,const mat4& mat);

    void SetVector3Array(const string& property,vector<vec3>& vec);
    void SetVector4Array(const string& property,vector<vec4>& vec);
    void SetFloatArray(const string& property,vector<float>& floats);
    void SetIntArray(const string& property,vector<int>& ints);
    void SetMatrixArray(const string& property,vector<mat4>& mat);

    void SetTexture(const string& property,ITexture2D*);//设置材质

    vec3 GetVector3(const string& property);
    vec4 GetVector4(const string& property);
    float GetFloat(const string& property);
    int GetInt(const string& property);
    mat4 GetMatrix(const string& property);

    vector<vec3> GetVector3Array(const string& property);
    vector<vec4> GetVector4Array(const string& property);

    vector<float> GetFloatArray(const string &property);
    vector<int> GetIntArray(const string& property);
    ITexture2D* GetTextures(const string& property);
    vector<mat4> GetMatrixArray(const string& property);

    void Update();

    inline const INative* GetNativePtr()const
    {return m_native;}

    Pass* CreatePass();
    void RemovePass(Pass* pass);

    inline void UsePass(Pass* pass)
    {m_current_pass=pass;}
    inline const Pass* GetCurrentPass()const
    {return m_current_pass;}

  protected:

    INative* m_native=nullptr;
    list<Pass> m_passes;
    Pass* m_current_pass=nullptr;
    list<Value> m_property_list;
    map<string,Value*> m_property_value;
  };

  class Material::INative
  {
  public:
    virtual void Upload(const list<Value>&)=0;
    virtual ~INative(){}
  };

  struct Material::Value
  {
    Value():data(1){}

    enum class Type:uint8_t
    {
      TEXTURE,VECTOR3,VECTOR4,FLOAT,INT,MATRIX/*float array*/
    };

    union _Internal
    {
      float _flaot;
      int _int;//int or color
    };

    string property_name;
    Type type;
    bool is_array=false;
    ITexture2D* _texture=nullptr;
    vector<_Internal> data;
  };
}

#endif
