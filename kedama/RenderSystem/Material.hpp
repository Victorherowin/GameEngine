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
#include "../GLMInclude.hpp"
#include "../Define.hpp"
#include "Interface/IShader.hpp"

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
    IShader* shader;
  };

  class KEDAMA_API Material
  {
  public:
    class INative;
    struct Value;

  public:
    Material();
    ~Material();

    void SetBool(const string& property,bool b);
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

    bool GetBool(const string& property);
    vec3 GetVector3(const string& property);
    vec4 GetVector4(const string& property);
    float GetFloat(const string& property);
    int GetInt(const string& property);
    mat4 GetMatrix(const string& property);

    vector<vec3> GetVector3Array(const string& property);
    vector<vec4> GetVector4Array(const string& property);

    vector<float> GetFloatArray(const string &property);
    vector<int> GetIntArray(const string& property);
    ITexture2D* GetTexture(const string& property);
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
      TEXTURE,VECTOR3,VECTOR4,FLOAT,INT,MATRIX,BOOL/*float array*/
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

  class DefaultMaterial:public Material
  {
  public:
    DefaultMaterial();
    inline void SetColor(const vec4& color){SetVector4("color",color);}
    inline void SetAmbient(const vec3& ambient,float strength=0.1f){SetVector4("ambient",vec4(ambient,strength));}
    inline void SetDiffuse(const vec3& diffuse){SetVector3("diffuse",diffuse);}
    inline void SetSpecular(const vec3& specular,float strength=0.5f){SetVector4("specular",vec4(specular,strength));}
    inline void SetShininess(float shininess){SetFloat("shininess",shininess);}
    inline void SetTexture(ITexture2D* tex){Material::SetTexture("texture0",tex);}

    inline vec4 GetColor(){return GetVector4("color");}
    inline vec4 GetAmbient(){return GetVector4("ambient");}
    inline vec3 GetDiffuse(){return GetVector3("diffuse");}
    inline vec4 GetSpecular(){return GetVector4("specular");}
    inline float GetShininess(){return GetFloat("shininess");}
    inline ITexture2D* GetTexture(){return Material::GetTexture("texture0");}

    inline void Update(){Material::Update();}
  };
}

#endif
