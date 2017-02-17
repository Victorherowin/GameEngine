#include "GLForwardRenderer.hpp"
#include "GLTexture2D.hpp"
#include "GLMeshNative.hpp"
#include "GLMaterialNative.hpp"
#include "GLShader.hpp"
#include "GLControl.hpp"

namespace Kedama {
  namespace GL {
    GLForwardRenderer::GLForwardRenderer(GLControl* control):m_control(control)
    {
      glGenProgramPipelines(1,&m_plo);
    }

    GLForwardRenderer::~GLForwardRenderer()
    {
      glDeleteProgramPipelines(1,&m_plo);
    }

    void GLForwardRenderer::Render(const RenderCommand& rc)
    {
      const GLMeshNative* nmesh = static_cast<const GLMeshNative*>(rc.mesh->GetNativePtr());
      const GLMaterialNative* nmaterial=static_cast<const GLMaterialNative*>(rc.material->GetNativePtr());
      const Pass* pass = rc.material->GetCurrentPass();
      GLShader* vs=static_cast<GLShader*>(pass->vertex_shader);
      GLShader* fs=static_cast<GLShader*>(pass->fragment_shader);

      GLint bindindex=0;
      for(auto& tex:nmaterial->GetTextures())
      {
        GLint localtion=glGetUniformLocation(fs->GetShader(),tex.first.c_str());
        if(localtion!=-1)
        {
          glProgramUniform1i(fs->GetShader(),localtion,bindindex);
          glBindTextureUnit(bindindex,static_cast<GLTexture2D*>(tex.second)->GetObj());
          ++bindindex;
        }
      }
      GLuint camera_ubo_index=glGetUniformBlockIndex(vs->GetShader(),"Camera");
      GLuint material_ubo_index=glGetUniformBlockIndex(fs->GetShader(),"Material");
      GLuint point_lights_ubo_index=glGetUniformBlockIndex(fs->GetShader(),"PointLights");
      GLuint spot_lights_ubo_index=glGetUniformBlockIndex(fs->GetShader(),"SpotLights");
      GLuint directional_lights_ubo_index=glGetUniformBlockIndex(fs->GetShader(),"DirectionalLights");
      if(camera_ubo_index!=GL_INVALID_INDEX)
      {
        glUniformBlockBinding(vs->GetShader(),camera_ubo_index,0);
        glBindBufferBase(GL_UNIFORM_BUFFER,0,m_control->GetCameraUBO());
      }
      if(point_lights_ubo_index!=GL_INVALID_INDEX)
      {
        glUniformBlockBinding(fs->GetShader(),point_lights_ubo_index,1);
        glBindBufferBase(GL_UNIFORM_BUFFER,1,m_control->GetPointLightsUBO());
      }
      if(spot_lights_ubo_index!=GL_INVALID_INDEX)
      {
        glUniformBlockBinding(fs->GetShader(),spot_lights_ubo_index,2);
        glBindBufferBase(GL_UNIFORM_BUFFER,2,m_control->GetSpotLightsUBO());
      }
      if(spot_lights_ubo_index!=GL_INVALID_INDEX)
      {
        glUniformBlockBinding(fs->GetShader(),directional_lights_ubo_index,3);
        glBindBufferBase(GL_UNIFORM_BUFFER,3,m_control->GetDirectionalLightsUBO());
      }
      if(spot_lights_ubo_index!=GL_INVALID_INDEX)
      {
        glUniformBlockBinding(fs->GetShader(),material_ubo_index,4);
        glBindBufferBase(GL_UNIFORM_BUFFER,4,nmaterial->GetUBO());
      }

      glBindProgramPipeline(m_plo);
      glUseProgramStages(m_plo,vs->GetGLTypeBit(),vs->GetShader());
      glUseProgramStages(m_plo,fs->GetGLTypeBit(),fs->GetShader());
      //glUseProgramStages(m_plo,GL_FRAGMENT_SHADER_BIT,m_gbuffer_shader);//PostProcessor需要（暂时鸽着）

      glBindVertexArray(nmesh->vao);
      if(pass->draw_mode==DrawMode::LINES)
        glDrawElements(GL_LINES,rc.mesh->GetIndices().size(),GL_UNSIGNED_INT,nullptr);
      else if(pass->draw_mode==DrawMode::NORMAL)
        glDrawElements(GL_TRIANGLES,rc.mesh->GetIndices().size(),GL_UNSIGNED_INT,nullptr);
      glBindVertexArray(0);
      glBindProgramPipeline(0);
    }

    //TODO:GLForwardRenderer 多实例渲染
    void GLForwardRenderer::Render(const MergedRenderCommand &mrc)
    {

    }

    //TODO:渲染阴影到阴影贴图
    void GLForwardRenderer::RenderShadow(const RenderCommand &rc)
    {

    }

    void GLForwardRenderer::RenderShadow(const MergedRenderCommand &mrc)
    {

    }
  }
}
