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

namespace Kedama
{
    using namespace glm;

    enum class DrawMode
    {
        LINES, TRIANGLES, POINT
    };

    enum class PassType
    {
        Normal, Transparent
    };

    struct KEDAMA_API Pass
    {
        //TODO:其他渲染设置
        PassType pass_type;
        DrawMode draw_mode = DrawMode::TRIANGLES;
        IShader* shader = nullptr;
    };

    enum class MaterialType
    {
        Normal, PostProcess
    };

    class KEDAMA_API Material
    {
    public:
        class INative;

        class KEDAMA_API Builder
        {
        public:
            template<typename T>
            Builder& AddProperty(const string& name, const T& default_value)
            {
                m_material->m_property_list.push_back(new PropertyValue<T>(name, default_value));
                m_material->m_property_value[name] = m_material->m_property_list.back();
                return *this;
            }

            template<typename T>
            Builder& AddProperty(const string& name)
            {
                m_material->m_property_list.push_back(new PropertyValue<T>(name));
                m_material->m_property_value[name] = m_material->m_property_list.back();
                return *this;
            }

            template<typename T>
            Builder& AddPropertyArray(const string& name, size_t length)
            {
                m_material->m_property_list.push_back(new PropertyValueArray<T>(name, length));
                m_material->m_property_value[name] = m_material->m_property_list.back();
                return *this;
            }

            template<typename T>
            Builder& AddPropertyArray(const string& name, size_t length, const initializer_list<T>& default_value)
            {
                m_material->m_property_list.push_back(new PropertyValue<T>(name));
                m_material->m_property_value[name] = m_material->m_property_list.back();
                return *this;
            }

            inline Material* Build()
            {
                m_material->m_type = MaterialType::Normal;
                m_material->Final();
                return m_material;
            }

        private:
            Material* m_material = new Material();
        };

    protected:
        Material();
        void Final();

    public:
        ~Material();

        template<typename T>
        PropertyValue<T> GetProperty(const string& name)
        {
            return *static_cast<PropertyValue<T>*>(m_property_value[name]);
        }

        template<typename T>
        PropertyValueArray<T> GetPropertyArray(const string& name)
        {
            return *static_cast<PropertyValueArray<T>*>(m_property_value[name]);
        }

        inline MaterialType GetType() { return m_type; }
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
        list <AbstractPropertyValue*> m_property_list;
        map<string, AbstractPropertyValue*> m_property_value;
    };

    class KEDAMA_API Material::INative
    {
    public:
        virtual void Init(const list <AbstractPropertyValue*>&)=0;

        virtual ~INative() {}
    };

    class PostProcessMaterial:public Material
    {
    private:
        PostProcessMaterial();
    public:
        class KEDAMA_API Builder:public Material::Builder
        {
        public:
            inline PostProcessMaterial* Build()
            {
                m_material->m_type = MaterialType::PostProcess;
                m_material->Final();
                return m_material;
            }

        private:
            PostProcessMaterial* m_material = new PostProcessMaterial();
        };
    };
}

#endif
