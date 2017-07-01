//
// Created by moe on 2017-06-04.
//

#ifndef KEDAMA_PROPERTYVALUE_HPP
#define KEDAMA_PROPERTYVALUE_HPP

#include "../Include.hpp"

namespace Kedama
{
    class ITexture2D;
    class ITexture2DArray;
    class ITexture3D;
    class ITextureCube;
    class ITextureCubeArray;

    using namespace std;

    class AbstractPropertyValue
    {
    public:
        using PropertyValueChanged=function<void(const AbstractPropertyValue&)>;

        AbstractPropertyValue(const string& property_name,const string& type):m_property_name(property_name),m_value_type(type){}
        inline const string& GetValueType()const{return m_value_type;}
        inline const string& GetPropertyValue()const{return m_property_name;}
        inline void AddValueChangedListener(const PropertyValueChanged& listener){listener(*this);m_value_changed_listeners.push_back(listener);}

        virtual const void* GetValueData()const=0;
        template<typename T>
        inline const T* GetValueData()const{return (const T*)GetValueData();}
    protected:
        inline void NotifyValueChanged(){for(auto listener:m_value_changed_listeners)listener(*this);}

    private:
        string m_property_name;
        const string& m_value_type;

        list<PropertyValueChanged> m_value_changed_listeners;
    };

    template<typename T>
    class PropertyValue:public AbstractPropertyValue
    {
    public:
        static const string ValueType;

        PropertyValue(const string& property_name,const T& default_value=T()):AbstractPropertyValue(property_name,ValueType),m_value(default_value){}
        inline void SetValue(const T& value){m_value=value;NotifyValueChanged();}
        inline const T& GetValue(){return m_value;}
        inline PropertyValue& operator =(const T& value){m_value=value;NotifyValueChanged();return *this;}
        inline PropertyValue& operator =(PropertyValue& value){m_value=value.m_value;NotifyValueChanged();return *this;}
        inline operator T(){return m_value;}
        inline operator const T()const{return m_value;}

        const void* GetValueData()const override{return &m_value;}

    private:
        T m_value;
    };

    template<typename T>
    class PropertyValueArray:public AbstractPropertyValue
    {
    public:
        class PropertyElementProxy
        {
        public:
            PropertyElementProxy(PropertyValueArray& outer,int i,T& value):m_outer(outer),m_pos(i),m_value(value){}

            inline PropertyElementProxy& operator =(const T& value)
            {
                m_value=value;
                m_outer.NotifyValueChanged();
                m_outer.NotifyElementChanged(m_pos);
                return *this;
            }

            inline PropertyElementProxy& operator =(PropertyElementProxy& value)
            {
                m_value=value.m_value;
                m_outer.NotifyValueChanged();
                m_outer.NotifyElementChanged(m_pos);
                return *this;
            }

            inline operator T(){return m_value;}
            inline operator const T()const{return m_value;}
            inline T* operator &(){return &m_value;}

        private:
            int m_pos;
            T& m_value;
            PropertyValueArray& m_outer;
        };

        class PropertyElementIterator
        {
        public:
            PropertyElementIterator(PropertyValueArray& outer,int i=numeric_limits<int>::max()):m_outer(outer),m_i(i) {}
            inline PropertyElementIterator& operator++() { ++m_i;return *this; }
            inline PropertyElementIterator& operator--() { --m_i;return *this;}
            inline PropertyElementIterator operator++(int) { return PropertyElementIterator(m_outer,m_i++);}
            inline PropertyElementIterator operator--(int) { return PropertyElementIterator(m_outer,m_i--);}
            inline bool operator==(PropertyElementIterator& pvi) { return ((&pvi.m_outer==&m_outer)&&(pvi.m_i==m_i))?true:false; }
            inline bool operator!=(PropertyElementIterator& pvi) { return !(*this==pvi);}
            inline PropertyElementProxy operator*(){return m_outer[m_i];}

        private:
            int m_i;
            PropertyValueArray& m_outer;
        };

    public:
        using ElementChanged=function<void(int i,const PropertyValueArray& pva)>;

        static const string ValueType;

        PropertyValueArray(const string& property_name,size_t size,const initializer_list<T>& default_value={}):AbstractPropertyValue(property_name,ValueType),m_size(size),m_value_array(new T[size])
        {
            int i=0;
            for(auto&& value:default_value)
                m_value_array[i++]=value;
        }

        ~PropertyValueArray(){delete[] m_value_array;}
        inline void AddElementChangedListener(const ElementChanged& listener){m_element_changed_listeners.push_back(listener);}

        inline PropertyElementProxy operator [](int index){return PropertyElementProxy(*this,index,m_value_array[index]);}
        inline const PropertyElementProxy operator [](int index)const{return PropertyElementProxy(const_cast<PropertyValueArray&>(*this),index,m_value_array[index]);}

        inline size_t Size(){return m_size;}
        inline PropertyElementIterator begin(){return PropertyElementIterator(*this,0);}
        inline PropertyElementIterator end(){return PropertyElementIterator(*this,m_size);}

        const void* GetValueData()const override{return m_value_array;}

    private:
        inline void NotifyElementChanged(int pos){for(auto& listener:m_element_changed_listeners)listener(pos,*this);}

    private:
        size_t m_size;
        T* m_value_array;
        list<ElementChanged> m_element_changed_listeners;
    };

    template<> class PropertyValueArray<ITexture2DArray>;
    template<> class PropertyValueArray<ITexture2D>;
    template<> class PropertyValueArray<ITextureCube>;
    template<> class PropertyValueArray<ITextureCubeArray>;
    template<> class PropertyValueArray<ITexture3D>;


    template<typename T>
    const string PropertyValue<T>::ValueType=typeid(T).name();

    template<typename T>
    const string PropertyValueArray<T>::ValueType=typeid(T[]).name();
}
#endif //KEDAMA_PROPERTYVALUE_HPP