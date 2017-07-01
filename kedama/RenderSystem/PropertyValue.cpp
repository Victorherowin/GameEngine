//
// Created by moe on 2017-07-01.
//

#include "../GLMInclude.hpp"
#include "PropertyValue.hpp"

#define DEFINE_PROPERTY_CLASS(c)\
template class PropertyValue<c>;\
template class PropertyValueArray<c>;

namespace Kedama
{
    using namespace glm;

    AbstractPropertyValue::AbstractPropertyValue(const string& property_name, const string& type)
            : m_property_name(property_name), m_value_type(type) {}

    AbstractPropertyValue::~AbstractPropertyValue() {}

    void AbstractPropertyValue::AddValueChangedListener(const PropertyValueChanged& listener)
    {
        listener(*this);
        m_value_changed_listeners.push_back(listener);
    }

    void AbstractPropertyValue::NotifyValueChanged()
    {
        for (auto listener:m_value_changed_listeners)
            listener(*this);
    }

    template<typename T>
    PropertyValue<T>::PropertyValue(const string& property_name, const T& default_value):
            AbstractPropertyValue(property_name, ValueType), m_value(default_value) {}

    template <typename T>
    PropertyValue<T>& PropertyValue<T>::operator=(PropertyValue& value)
    {
        m_value=value.m_value;
        NotifyValueChanged();
        return *this;
    }

    template <typename T>
    PropertyValue<T>& PropertyValue<T>::operator=(const T& value)
    {
        m_value=value;
        NotifyValueChanged();
        return *this;
    }

    template <typename T>
    void PropertyValue<T>::SetValue(const T& value)
    {
        m_value=value;
        NotifyValueChanged();
    }

    template <typename T>
    void PropertyValueArray<T>::NotifyElementChanged(int pos)
    {
        for(auto& listener:m_element_changed_listeners)
            listener(pos,*this);
    }



    template <typename T>
    PropertyValueArray<T>::PropertyValueArray(const string& property_name, size_t size,
                                           const initializer_list<T>& default_value):
            AbstractPropertyValue(property_name,ValueType),m_size(size),m_value_array(new T[size])
    {
        int i=0;
        for(auto&& value:default_value)
            m_value_array[i++]=value;
    }

    template <typename T>
    PropertyValueArray<T>::~PropertyValueArray()
    {
        delete[] m_value_array;
    }

    DEFINE_PROPERTY_CLASS(int16_t)
    DEFINE_PROPERTY_CLASS(int32_t)
    DEFINE_PROPERTY_CLASS(float)
    DEFINE_PROPERTY_CLASS(vec2)
    DEFINE_PROPERTY_CLASS(vec3)
    DEFINE_PROPERTY_CLASS(vec4)
    DEFINE_PROPERTY_CLASS(ivec2)
    DEFINE_PROPERTY_CLASS(ivec3)
    DEFINE_PROPERTY_CLASS(ivec4)
    DEFINE_PROPERTY_CLASS(mat2)
    DEFINE_PROPERTY_CLASS(mat3)
    DEFINE_PROPERTY_CLASS(mat4)

    DEFINE_PROPERTY_CLASS(ITexture2DArray*)
    DEFINE_PROPERTY_CLASS(ITexture2D*)
    DEFINE_PROPERTY_CLASS(ITextureCube*)
    DEFINE_PROPERTY_CLASS(ITextureCubeArray*)
    DEFINE_PROPERTY_CLASS(ITexture3D*)
}
