#ifndef _H_KEDAMA_SINGLETON
#define _H_KEDAMA_SINGLETON

#include <cassert>

namespace Kedama
{
    template<typename T>
    class Singleton
    {
        public:
        Singleton()
        {
            assert(m_obj==nullptr);
            if(m_obj==nullptr)
                m_obj=static_cast<T*>(this);
        }
        
        ~Singleton()
        {
            if(m_obj!=nullptr)
                m_obj=nullptr;
        }
        
        Singleton(const Singleton&)=delete;
        Singleton(Singleton&&)=delete;
        
        static T* GetSingletonPtr()
        {
            return m_obj;
        }
        
        static T& GetSingleton()
        {
            return *m_obj;
        }
        
        private:
        static T* m_obj;
    };
    
    template<typename T>
    T* Singleton<T>::m_obj=nullptr;
}

#endif