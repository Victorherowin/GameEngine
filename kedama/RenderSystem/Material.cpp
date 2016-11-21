#include "Material.hpp"

namespace Kedama {

  void Material::SetColor(const u8vec4& color)
  {
    m_color=color;
  }

  void Material::SetAmbientColor(const u8vec4& color)
  {
    m_ambient_color=color;
  }

  void Material::SetDiffuseColor(const u8vec4& color)
  {
    m_diffuse_color=color;
  }

  void Material::SetSpecularColorAndShininess(const u8vec4 &color, float shininess)
  {
    m_specular_color=color;
    m_specular_shininess=shininess;
  }

  Pass& Material::CreatePass()
  {
    m_passes.push_back(Pass());
    return m_passes.back();
  }

  MaterialPtr Material::CreateMaterial()
  {
    return std::make_shared<Material>();
  }
}
