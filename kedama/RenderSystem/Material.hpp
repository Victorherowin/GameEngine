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
#include "PropertyValue.hpp"

namespace Kedama {
    using namespace glm;

    enum class DrawMode {
        LINES, TRIANGLES, POINT
    };

    enum class PassType {
        Normal, Transparent
    };

    struct KEDAMA_API Pass {
        //TODO:其他渲染设置
        PassType pass_type;
        DrawMode draw_mode = DrawMode::TRIANGLES;
        IShader* shader = nullptr;
    };

    enum class MaterialType {
        Normal, PostProcess
    };

    class KEDAMA_API Material
    {
    public:
        class INative;
    protected:
        Material(MaterialType type);

    public:
        Material();

        ~Material();

        template<typename T>
        Material &AddProperty(const string &name, const T &default_value)
        {
            m_property_list.push_back(PropertyValue<T>(name,default_value));
            m_property_value[name]=&m_property_list.back();
            return *this;
        }

        template<typename T>
        Material &AddProperty(const string &name)
        {
            m_property_list.push_back(PropertyValue<T>(name));
            m_property_value[name]=&m_property_list.back();
            return *this;
        }

        template<typename T>
        Material &AddPropertyArray(const string &name, size_t length)
        {
            m_property_list.push_back(PropertyValueArray<T>(name,length));
            m_property_value[name]=&m_property_list.back();
            return *this;
        }

        template<typename T>
        Material &AddPropertyArray(const string &name, size_t length, const initializer_list<T>& default_value)
        {
            m_property_list.push_back(PropertyValue<T>(name));
            m_property_value[name]=&m_property_list.back();
            return *this;
        }

        void Final();

        template<typename T>
        PropertyValue<T> GetProperty(const string &name)
        {
            return *static_cast<PropertyValue<T>*>(m_property_value[name]);
        }

        template<typename T>
        PropertyValueArray<T> GetPropertyArray(const string &name)
        {
            return *static_cast<PropertyValueArray<T>*>(m_property_value[name]);
        }

/*    void SetBool(const string& property,bool b);
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
    vector<mat4> GetMatrixArray(const string& property);*/

        inline MaterialType GetType() { return m_type; }

        void Update();

        inline const INative* GetNativePtr() const { return m_native; }

        Pass* CreatePass();

        void RemovePass(Pass* pass);

        inline void UsePass(Pass* pass) { m_current_pass = pass; }

        inline const Pass* GetCurrentPass() const { return m_current_pass; }

    protected:

        MaterialType m_type;

        static Pass default_pass;

        INative* m_native = nullptr;
        list <Pass> m_passes;
        Pass* m_current_pass = nullptr;
        list <AbstractPropertyValue> m_property_list;
        map<string, AbstractPropertyValue*> m_property_value;
    };

    class KEDAMA_API Material::INative {
    public:
        virtual void Init(const list <AbstractPropertyValue>&)=0;

        virtual ~INative() {}
    };


    class PostProcessMaterial : public Material {
    public:
        PostProcessMaterial();
    };

    class DefaultMaterial : public Material {
    public:
        DefaultMaterial();

        inline void SetColor(const vec4 &color) {  GetProperty<vec4>("color")=color; }

        inline void SetAmbient(const vec3 &ambient, float strength = 0.1f) {
            GetProperty<vec4>("ambient")=vec4(ambient, strength);
        }

        inline void SetDiffuse(const vec3 &diffuse) { GetProperty<vec3>("diffuse")=diffuse; }

        inline void SetSpecular(const vec3 &specular, float strength = 0.5f) {
            GetProperty<vec4>("specular")=vec4(specular, strength);
        }

        inline void SetShininess(float shininess) { GetProperty<float>("shininess")=shininess; }

        inline void SetTexture(ITexture2D* tex) { GetProperty<ITexture2D*>("texture0")=tex; }

        inline vec4 GetColor() { return GetProperty<vec4>("color"); }

        inline vec4 GetAmbient() { return GetProperty<vec4>("ambient"); }

        inline vec3 GetDiffuse() { return GetProperty<vec3>("diffuse"); }

        inline vec4 GetSpecular() { return GetProperty<vec4>("specular"); }

        inline float GetShininess() { return GetProperty<float>("shininess"); }

        inline ITexture2D* GetTexture() { return GetProperty<ITexture2D*>("texture0"); }
    };
}

#endif
