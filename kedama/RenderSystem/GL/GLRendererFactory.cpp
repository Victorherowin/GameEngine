#include "GLRendererFactory.hpp"
#include "GLShader.hpp"
#include "GLTexture2D.hpp"
#include "GLMeshNative.hpp"
#include "GLMaterialNative.hpp"
#include "GLLightNative.hpp"
#include "GLControl.hpp"

namespace Kedama
{
  namespace GL
  {
    Mesh::INative* GLRenderSystemFactory::CreateMeshNative()
    {
      return new GLMeshNative();
    }

    Material::INative* GLRenderSystemFactory::CreateMaterialNative()
    {
      return new GLMaterialNative();
    }

	Light::INative* GLRenderSystemFactory::CraeteLightNative()
	{
		return new GLLightNative();
	}

    ITexture2D* GLRenderSystemFactory::CreateTexture2D()
    {
      return new GLTexture2D();
    }

    IShader* GLRenderSystemFactory::CreateShader()
    {
      return new GLShader();
    }

    IControl* GLRenderSystemFactory::GetControl()
    {
      if(m_control==nullptr)
        m_control=new GLControl();
      return m_control;
    }

    const string GLRenderSystemFactory::GetShaderLanguage()
    {
      return "GLSL 4.50";
    }
  }
}
