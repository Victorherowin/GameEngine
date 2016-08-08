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

    const u8vec4& GetColor(){return m_color;}
    const u8vec4& GetAmbientColor(){return m_ambient_color;}
    const u8vec4& GetDiffuseColor(){return m_diffuse_color;}
    const u8vec4& GetSpecularColor(){return m_specular_color;}
    float GetShininess(){return m_specular_shininess;}

    void AddPass(const FrameBufferPtr& src,const FrameBufferPtr& dst,const IShaderPtr& shader);
    const vector<Pass>& GetPass()const{return m_pass;}
    const ITexture2DPtr& GetTexture()const{return m_tex2d;}

    const PassPtr& GetPass(int at);

    void BindTexture(const ITexture2DPtr& tex);

    static MaterialPtr CreateMaterial();
  protected:

    vector<Pass> m_pass;

    u8vec4 m_color;

    u8vec4 m_ambient_color;
    u8vec4 m_diffuse_color;
    u8vec4 m_specular_color;
    float m_specular_shininess=0.0f;

    ITexture2DPtr m_tex2d;

    ITexture2DPtr m_normal_tex;
    //...
  };
}

#endif
