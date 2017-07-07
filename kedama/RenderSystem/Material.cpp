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

    Material* Material::MakeDefaultMaterial()
    {
        return Builder()
				.AddProperty("use_texture",false)
                .AddProperty("color", vec4(0.1f, 0.2f, 0.3f, 1.0f))
                .AddProperty("ambient", vec4(0.1f, 0.2f, 0.3f, 0.1f))
                .AddProperty("diffuse", vec3(0.4f, 0.5f, 0.6f))
                .AddProperty("specular", vec4(0.7f, 0.8f, 0.9f, 0.5f))
                .AddProperty("shininess", 0.8f)
                .Build();
    }
}

namespace Kedama
{
    PostProcessMaterial::PostProcessMaterial()
    {}
}