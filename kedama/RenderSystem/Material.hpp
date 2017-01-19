#ifndef MATERIAL
#define MATERIAL

#include "ITexture2D.hpp"
#include "../Include.hpp"
#include "../Define.hpp"
#include "Shader.hpp"

namespace Kedama
{
  using namespace glm;

  class KEDAMA_API Pass
  {
  public:
    //TODO:其他渲染设置
    Shader* m_vertex_shader;
    Shader* m_fragment_shader;
  };

  class KEDAMA_API Material
  {
  public:
    Material();
    ~Material();

    void SetColor(const string& property,const u8vec4& color);//RGBA
    void SetFloat(const string& property,float _float);
    void SetInt(const string& property,int _int);
    void SetMatrix(const string& property,const mat4& mat);

    void SetColorArray(const string& property,vector<u8vec4>& colors);
    void SetFloatArray(const string& property,vector<float>& floats);
    void SetIntArray(const string& property,vector<int>& ints);
    void SetMatrixArray(const string& property,vector<mat4>& mat);

    void SetTexture(const string& property,ITexture2D*);//设置材质



    u8vec4 GetColor(const string& property);
    float GetFloat(const string& property);
    int GetInt(const string& property);
    mat4 GetMatrix(const string& property);

    vector<u8vec4> GetColorArray(const string& property);
    vector<float> GetFloatArray(const string &property);
    vector<int> GetIntArray(const string& property);
    ITexture* GetTextures(const string& property);
    vector<mat4> GetMatrixArray(const string& property);

    Pass* CreatePass();
    void RemovePass(Pass*);

    const list<Pass>& GetPasses()const{return m_passes;}
  public:
    class Native;
    struct Value;

  protected:

    Native* m_native=nullptr;
    list<Pass> m_passes;
    list<Value> m_property_list;
    map<string,Value*> m_property_value;
  };

  class Material::Native
  {
  public:
    virtual void Upload(const list<Value>&)=0;
    virtual ~Native(){}
  };

  struct Material::Value
  {
    Value():data(1){}

    enum class Type:uint8_t
    {
      TEXTURE,COLOR,FLOAT,INT,MATRIX/*float array*/
    };

    union _Internal
    {
      float _flaot;
      int _int;//int or color
    };

    string property_name;
    Type type;
    bool is_array=false;
    ITexture* _texture=nullptr;
    vector<_Internal> data;
  };
}

#endif
