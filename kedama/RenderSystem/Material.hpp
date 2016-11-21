#ifndef MATERIAL
#define MATERIAL

#include "ITexture2D.hpp"
#include "../Include.hpp"
#include "../Define.hpp"
#include "FrameBuffer.hpp"
#include "Shader.hpp"

namespace Kedama
{
  using namespace glm;

  DEFINE_SHARED_PTR(Material)

  class KEDAMA_API Pass
  {
    public:
    //TODO:其他渲染设置
    ShaderPtr m_vertex_shader;
    ShaderPtr m_fragment_shader;
  };

  class KEDAMA_API Material
  {
  public:

    void SetColor(const u8vec4& color);//RGBA
    void SetAmbientColor(const u8vec4& color);
    void SetDiffuseColor(const u8vec4& color);
    void SetSpecularColorAndShininess(const u8vec4& color,float shininess);
    const void SetTexture(const string& name,ITexture2DPtr);

    const u8vec4& GetColor(){return m_color;}
    const u8vec4& GetAmbientColor(){return m_ambient_color;}
    const u8vec4& GetDiffuseColor(){return m_diffuse_color;}
    const u8vec4& GetSpecularColor(){return m_specular_color;}
    float GetShininess(){return m_specular_shininess;}

    Pass& CreatePass();
    const vector<Pass>& GetPasses()const{return m_passes;}
    const ITexture2DPtr& GetTexture()const{return m_tex2d;}

    const vector<Pass> GetPasses(int at);

    void BindTexture(const ITexture2DPtr& tex);

    static MaterialPtr CreateMaterial();
  protected:

    vector<Pass> m_passes;
    vector<pair<string,ITexture2DPtr>> m_textures;

    u8vec4 m_color;

    u8vec4 m_ambient_color;
    u8vec4 m_diffuse_color;
    u8vec4 m_specular_color;
    float m_specular_shininess=0.0f;
  };
}

#endif
