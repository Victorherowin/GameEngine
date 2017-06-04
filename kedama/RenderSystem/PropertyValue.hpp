//
// Created by moe on 2017-06-04.
//

#ifndef KEDAMA_PROPERTYVALUE_HPP
#define KEDAMA_PROPERTYVALUE_HPP

#include "../Include.hpp"

namespace Kedama
{
    using namespace std;

    class AbstractPropertyValue
    {
    public:
        using PropertyValueChanged=function<void(const AbstractPropertyValue&)>;

        AbstractPropertyValue(const string& property_name,const char* type):m_property_name(property_name),m_value_type(type){}
        inline const char* GetValueType(){return m_value_type;}

        inline void AddValueChangedListener(const PropertyValueChanged& listener){listener(*this);m_value_changed_listeners.push_back(listener);}

        virtual void* GetValueData()=0;

    protected:
        void NotifyValueChanged(){for(auto listener:m_value_changed_listeners)listener(*this);}

    private:
        string m_property_name;
        const char* m_value_type;

        list<PropertyValueChanged> m_value_changed_listeners;
    };


    template<typename T>
    class PropertyValue:public AbstractPropertyValue
    {
    public:
        static const char* ValueType;

        PropertyValue(const string& property_name):AbstractPropertyValue(property_name,ValueType){}
        inline void SetValue(const T& value){m_value=value;NotifyValueChanged();}
        inline const T& GetValue(){return m_value;}
        inline PropertyValue& operator =(const T& value){m_value=value;NotifyValueChanged();return *this;}
        inline PropertyValue& operator =(PropertyValue& value){m_value=value.m_value;NotifyValueChanged();return *this;}

        void* GetValueData()override{return &m_value;}

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
            PropertyElementProxy(PropertyValueArray& outer,T& value):m_outer(outer),m_value(value){}

            PropertyElementProxy& operator =(const T& value)
            {
                m_value=value;
                m_outer.NotifyValueChanged();
                m_outer.NotifyElementChanged();
                return *this;
            }

            PropertyElementProxy& operator =(PropertyElementProxy& value)
            {
                m_value=value.m_value;
                m_outer.NotifyValueChanged();
                m_outer.NotifyElementChanged();
                return *this;
            }

            operator T(){return m_value;}
            T* operator &(){return &m_value;}

        private:
            T& m_value;
            PropertyValueArray& m_outer;
        };

        class PropertyElementIterator
        {
        public:
            PropertyElementIterator(PropertyValueArray& outer,uint32_t i=numeric_limits<uint32_t>::max()):m_outer(outer),m_i(i) {}
            inline PropertyElementIterator& operator++() { if(m_i>=m_outer.Size())m_i=numeric_limits<uint32_t>::max();return m_outer[++m_i]; }
            inline PropertyElementIterator& operator--() { if(m_i>=m_outer.Size())m_i=numeric_limits<uint32_t>::max();return m_outer[--m_i]; }
            inline PropertyElementIterator operator++(int) { if(m_i>=m_outer.Size())m_i=numeric_limits<uint32_t>::max();return m_outer[m_i++]; }
            inline PropertyElementIterator operator--(int) { if(m_i>=m_outer.Size())m_i=numeric_limits<uint32_t>::max();return m_outer[m_i--]; }
            inline bool operator==(PropertyElementIterator& pvi) { return ((&pvi.m_outer==&m_outer)&&(pvi.m_i==m_i))?true:false; }
            inline bool operator!=(PropertyElementIterator& pvi) {return !(*this==pvi);}

        private:
            uint32_t m_i;
            PropertyValueArray& m_outer;
        };

    public:
        using ElementChanged=function<void(int i,const PropertyValueArray& pva)>;

        static const char* ValueType;

        PropertyValueArray(const string& property_name):AbstractPropertyValue(property_name,ValueType){}
        inline void AddElementChangedListener(const ElementChanged& listener){m_element_changed_listeners.push_back(listener);}

        inline void AddValue(const T& value);
        inline PropertyElementProxy operator [](int index){return PropertyElementProxy(*this,m_value_array[index]);}
        inline size_t Size(){return m_value_array.size();}
        inline bool Empty(){return m_value_array.empty();}
        inline PropertyElementIterator begin(){return PropertyElementIterator(*this,0u);}
        inline PropertyElementIterator end(){return PropertyElementIterator(*this);}

        void* GetValueData()override{return m_value_array.data();}

    private:
        void NotifyElementChanged(){for(int i=0;i<m_element_changed_listeners.size();++i)(i,*this);}

    private:
        vector<T> m_value_array;
        list<ElementChanged> m_element_changed_listeners;
    };

    template<typename T>
    const char* PropertyValue<T>::ValueType=typeid(T).name();

    template<typename T>
    const char* PropertyValueArray<T>::ValueType=typeid(vector<T>).name();
}

#endif //KEDAMA_PROPERTYVALUE_HPP
