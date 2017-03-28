#include "Material.hpp"
#include "../Engine.hpp"

#define GETPROPERTY(val_type,_type,property) {\
  auto it=m_property_value.find(property);\
  if(it==m_property_value.end())\
    throw runtime_error("Not Found Value!(property:"+(property)+")");\
  if(it->second->type!=Value::Type::_type)\
    throw runtime_error("Type Error");\
  return *(val_type*)&it->second->data[0];\
}

#define GETPROPERTYARRAY(val_type,_type,property,out_v,n) {\
  auto it=m_property_value.find(property);\
  if(it==m_property_value.end())\
    throw runtime_error("Not Found Value!(property:"+(property)+")");\
  if(it->second->type!=Value::Type::_type||!it->second->is_array)\
    throw runtime_error("Type Error");\
  out_v=(val_type*)it->second->data.data();\
  n=it->second->data.size();\
}

#define SETPROPERTY(_type,property,val) {\
  Value v;\
  v.type=Value::Type::_type;\
  v.property_name=property;\
  v.data[0]=*(Value::_Internal*)&val;\
  auto it=m_property_value.find(property);\
  if(it==m_property_value.end())\
  {\
    m_property_list.push_back(v);\
    m_property_value[property]=&m_property_list.back();\
  }\
  else\
  {\
    *(m_property_value[property])=v;\
  }\
}

#define SETPROPERTYARRAY(_type,property,val,size) {\
  Value v;\
  v.is_array=true;\
  v.property_name=property;\
  v.type=Value::Type::_type;\
  Value::_Internal* p=(Value::_Internal*)&val[0];\
  v.data.clear();\
  v.data.insert(v.data.begin(),p,p+size);\
  auto it=m_property_value.find(property);\
  if(it==m_property_value.end())\
  {\
    m_property_list.push_back(v);\
    m_property_value[property]=&m_property_list.back();\
  }\
  else\
  {\
    *(m_property_value[property])=v;\
  }\
}

namespace Kedama {

  Pass Material::default_pass;

  Material::Material(MaterialType type):m_type(type)
  {
    m_native=Engine::GetSingleton().GetRendererFactory()->CreateMaterialNative();
    m_current_pass=&default_pass;
  }

  Material::Material():Material(MaterialType::Normal)
  {
  }

  Material::~Material()
  {
    delete m_native;
  }

  void Material::SetBool(const string &property, bool b)
  {
    int _b=b;
    SETPROPERTY(BOOL,property,_b);
  }

  void Material::SetVector3(const string& property,const vec3& vec)
  {
    SETPROPERTYARRAY(VECTOR3,property,vec,3);
    m_property_value[property]->is_array=false;
  }

  void Material::SetVector3Array(const string &property, vector<vec3> &vec)
  {
    SETPROPERTYARRAY(VECTOR3,property,vec.data(),vec.size()*3);
  }

  void Material::SetVector4(const string& property,const vec4& vec)
  {
    SETPROPERTYARRAY(VECTOR4,property,vec,4);
    m_property_value[property]->is_array=false;
  }

  void Material::SetVector4Array(const string &property, vector<vec4> &vec)
  {
    SETPROPERTYARRAY(VECTOR4,property,vec.data(),vec.size()*4);
  }

  void Material::SetFloat(const string &property, float _float)
  {
    SETPROPERTY(FLOAT,property,_float)
  }

  void Material::SetFloatArray(const string &property, vector<float> &_floats)
  {
    SETPROPERTYARRAY(FLOAT,property,_floats,_floats.size())
  }

  void Material::SetInt(const string &property, int _int)
  {
    SETPROPERTY(INT,property,_int)
  }

  void Material::SetIntArray(const string &property, vector<int> &_ints)
  {
    SETPROPERTYARRAY(INT,property,_ints,_ints.size())
  }

  void Material::SetTexture(const string &property, ITexture2D* _texture)
  {
    Value v;
    v.property_name=property;
    v.type=Value::Type::TEXTURE;
    v._texture=_texture;
    auto it=m_property_value.find(property);
    if(it==m_property_value.end())
    {
      m_property_list.push_back(v);
      m_property_value[property]=&m_property_list.back();
    }
    else
    {
      *(m_property_value[property])=v;
    }
  }

  void Material::SetMatrix(const string &property, const mat4 &mat)
  {
    SETPROPERTYARRAY(MATRIX,property,mat[0],16);
    m_property_value[property]->is_array=false;
  }

  void Material::SetMatrixArray(const string &property, vector<mat4> &mats)
  {
    SETPROPERTYARRAY(MATRIX,property,mats.data(),mats.size()*16);
  }

  //Get
  vec3 Material::GetVector3(const string &property)
  {
    GETPROPERTY(vec3,VECTOR3,property);
  }

  vec4 Material::GetVector4(const string &property)
  {
    GETPROPERTY(vec4,VECTOR4,property);
  }

  vector<vec4> Material::GetVector4Array(const string &property)
  {
    vec4* p;
    int n;
    GETPROPERTYARRAY(vec4,VECTOR4,property,p,n);
    vector<vec4> v(n);
    v.insert(v.begin(),p,p+n);
    return v;
  }

  float Material::GetFloat(const string &property)
  {
    GETPROPERTY(float,FLOAT,property);
  }

  vector<float> Material::GetFloatArray(const string &property)
  {
    float* p;
    int n;
    GETPROPERTYARRAY(float,FLOAT,property,p,n);
    vector<float> v(n);
    v.insert(v.begin(),p,p+n);
    return v;
  }

  int Material::GetInt(const string &property)
  {
    GETPROPERTY(int,INT,property)
  }

  vector<int> Material::GetIntArray(const string &property)
  {
    int* p;
    int n;
    GETPROPERTYARRAY(int,INT,property,p,n);
    vector<int> v(n);
    v.insert(v.begin(),p,p+n);
    return v;
  }

  mat4 Material::GetMatrix(const string& property)
  {
    auto it=m_property_value.find(property);
    if(it==m_property_value.end())
      throw runtime_error("Not Found Value!(property:"+(property)+")");
    if(it->second->type!=Value::Type::MATRIX)
      throw runtime_error("Type Error");
    mat4 mat;
    memcpy(&mat[0][0],it->second->data.data(),16*4);
    return mat;
  }

  vector<mat4> Material::GetMatrixArray(const string &property)
  {
    mat4* p;
    int n;
    GETPROPERTYARRAY(mat4,MATRIX,property,p,n);
    vector<mat4> v(n);
    v.insert(v.begin(),p,p+n);
    return v;
  }

  ITexture2D* Material::GetTexture(const string& property)
  {
    auto it=m_property_value.find(property);
    if(it==m_property_value.end())
      throw runtime_error("Not Found Value!(property:"+(property)+")");
    return it->second->_texture;
  }

  Pass* Material::CreatePass()
  {
    m_passes.push_back(Pass());
    return &m_passes.back();
  }

  void Material::RemovePass(Pass* pass)
  {
    for(auto it=m_passes.begin();it!=m_passes.end();++it)
    {
      if(&*it==pass)
      {
        m_passes.erase(it);
        break;
      }
    }
  }

  void Material::Update()
  {
    m_native->Upload(m_property_list);
  }

}

namespace Kedama {
  PostProcessMaterial::PostProcessMaterial():Material(MaterialType::PostProcess)
  {
  }
}

namespace Kedama {
  DefaultMaterial::DefaultMaterial()
  {
    SetBool("use_texture",false);
    SetVector4("color",vec4(0.1f,0.2f,0.3f,1.0f));
    SetVector4("ambient",vec4(0.1f,0.2f,0.3f,0.1f));
    SetVector3("diffuse",vec3(0.4f,0.5f,0.6f));
    SetVector4("specular",vec4(0.7f,0.8f,0.9f,0.5f));
    SetFloat("shininess",0.8);
    Update();
  }
}
