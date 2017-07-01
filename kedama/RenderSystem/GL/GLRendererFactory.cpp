#include "GLSkinner.hpp"
#include "GLRendererFactory.hpp"
#include "GLShader.hpp"
#include "GLTexture2D.hpp"
#include "GLMaterialNative.hpp"
#include "GLLightNative.hpp"
#include "GLControl.hpp"

namespace Kedama
{
  namespace GL
  {
    IMeshBuffer* GLRenderSystemFactory::CreateMeshBuffer(size_t vertex_num,size_t index_num)
    {
      return new GLMeshBuffer(vertex_num,index_num);
    }

    ISkinner* GLRenderSystemFactory::CreateSkinner(IMeshBuffer* mesh,Joint* joint)
    {
      return new GLSkinner(mesh,joint);
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
