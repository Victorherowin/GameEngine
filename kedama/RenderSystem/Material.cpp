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

  void Material::AddPass(FrameBufferPtr &src, FrameBufferPtr &dst, IShaderPtr shader)
  {
    Pass pass;
    pass.m_src_framebuffer=src;
    pass.m_dst_framebuffer=dst;
    pass.m_shader=shader;
    m_pass.push_back(pass);
  }

  void Material::BindTexture(ITexture2DPtr tex)
  {
    m_tex2d=tex;
  }
}
