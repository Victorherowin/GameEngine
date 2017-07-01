#include "Material.hpp"
#include "../Engine.hpp"

namespace Kedama
{
    Pass Material::default_pass;
    Material::Material()
    {
        m_native = Engine::GetSingleton().GetRendererFactory()->CreateMaterialNative();
        m_current_pass = &default_pass;
    }

    Material::~Material()
    {
        for(auto p : m_property_list)
            delete p;
        delete m_native;
    }

    Pass* Material::CreatePass()
    {
        m_passes.push_back(Pass());
        return &m_passes.back();
    }

    void Material::RemovePass(Pass* pass)
    {
        for (auto it = m_passes.begin(); it != m_passes.end(); ++it) {
            if (&*it == pass) {
                m_passes.erase(it);
                break;
            }
        }
    }

    void Material::Final()
    {
        m_native->Init(m_property_list);
    }
}

namespace Kedama
{
    PostProcessMaterial::PostProcessMaterial()
    {}
}