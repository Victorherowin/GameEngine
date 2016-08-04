#ifndef MATERIAL
#define MATERIAL

#include "ITexture2D.hpp"
#include "IShader.hpp"
#include "../Config.hpp"
#include "FrameBuffer.hpp"
#include <glm/integer.hpp>

namespace Kedama
{
  using namespace glm;

  DEFINE_SHARED_PTR(Material)
  DEFINE_SHARED_PTR(Pass)

  class KEDAMA_API InstancingInfo
  {
//
  };

  class KEDAMA_API Pass
  {
    public:
    FrameBufferPtr m_src_framebuffer;
    FrameBufferPtr m_dst_framebuffer;
    IShaderPtr m_shader;
    InstancingInfo m_instancing_info;

  };

  class KEDAMA_API Material
  {
  public:

    void SetColor(const u8vec4& color);//RGBA
    void SetAmbientColor(const u8vec4& color);
    void SetDiffuseColor(const u8vec4& color);
    void SetSpecularColorAndShininess(const u8vec4& color,float shininess);
    void AddPass(FrameBufferPtr& src,FrameBufferPtr& dst,IShaderPtr shader);

    const PassPtr& GetPass(int at);

    void BindTexture2D(const string& name,ITexture2DPtr tex);
    //void BindTexture3D(const string& name,ITexture3D* tex);
    //void BindTextureCube(const string& name,ITextureCube* tex);
  protected:

    vector<Pass> m_pass;

    u8vec4 m_color;

    u8vec4 m_ambient_color;
    u8vec4 m_diffuse_color;
    u8vec4 m_specular_color;
    float m_specular_shininess=0.0f;

    ITexture2DPtr m_tex_2ds;
  };
}

#endif
