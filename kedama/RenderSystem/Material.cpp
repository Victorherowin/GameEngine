#include "Material.hpp"

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

  void Material::SetColor(const string& property,const u8vec4& _color)
  {
    int _int=*(int*)&_color[0];

    SETPROPERTY(COLOR,property,_int)
  }

  void Material::SetColorArray(const string &property, vector<u8vec4> &colors)
  {
    int* _int_array =(int*)colors.data();
    SETPROPERTYARRAY(COLOR,property,_int_array,colors.size());
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
    SETPROPERTYARRAY(MATRIX,property,mats.data(),mats.size());
  }

  //Get
  u8vec4 Material::GetColor(const string &property)
  {
    GETPROPERTY(u8vec4,COLOR,property);
  }

  vector<u8vec4> Material::GetColorArray(const string &property)
  {
    u8vec4* p;
    int n;
    GETPROPERTYARRAY(u8vec4,COLOR,property,p,n);
    vector<u8vec4> v(n);
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

  ITexture2D* Material::GetTextures(const string& property)
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

}
