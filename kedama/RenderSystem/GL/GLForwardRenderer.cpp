#include "GLForwardRenderer.hpp"
#include "GLTexture2D.hpp"
#include "GLMeshNative.hpp"
#include "GLMaterialNative.hpp"
#include "GLShader.hpp"
#include "GLControl.hpp"

#define MODEL_MATRIX_INDEX 4

namespace Kedama {
  namespace GL {
    GLForwardRenderer::GLForwardRenderer(GLControl* control):m_control(control)
    {
      glCreateBuffers(1,&m_model_matrix_ubo);
      glNamedBufferStorage(m_model_matrix_ubo,sizeof(mat4)*1000,nullptr,GL_MAP_WRITE_BIT|GL_MAP_PERSISTENT_BIT|GL_MAP_COHERENT_BIT);
      m_model_matrix_ubo_data=(mat4*)glMapNamedBufferRange(m_model_matrix_ubo,0,sizeof(mat4)*1000,GL_MAP_WRITE_BIT|GL_MAP_PERSISTENT_BIT|GL_MAP_COHERENT_BIT);
    }

    GLForwardRenderer::~GLForwardRenderer()
    {
      glDeleteBuffers(1,&m_model_matrix_ubo);
    }

    void GLForwardRenderer::Render(const RenderCommand& rc)
    {
      MergedRenderCommand mrc;
      mrc.material=rc.material;
      mrc.mesh=rc.mesh;
      mrc.transforms.push_back(rc.transform);
      Render(mrc);
    }

    void GLForwardRenderer::Render(const MergedRenderCommand &mrc)
    {
      const GLMeshNative* nmesh = static_cast<const GLMeshNative*>(mrc.mesh->GetNativePtr());
      const GLMaterialNative* nmaterial=static_cast<const GLMaterialNative*>(mrc.material->GetNativePtr());
      const Pass* pass = mrc.material->GetCurrentPass();
      GLShader* program=static_cast<GLShader*>(pass->shader);

      mat4* i=m_model_matrix_ubo_data;
      for(Transform* t:mrc.transforms)
      {
        memcpy(i,glm::value_ptr(t->GetModelMatrix()),sizeof(mat4));
        ++i;
      }

      GLint bindindex=0;
      for(auto& tex:nmaterial->GetTextures())
      {
        GLint localtion=glGetUniformLocation(program->GetShader(),tex.first.c_str());
        if(localtion!=-1)
        {
          glProgramUniform1i(program->GetShader(),localtion,bindindex);
          glBindTextureUnit(bindindex,static_cast<GLTexture2D*>(tex.second)->GetObj());
          ++bindindex;
        }
      }

      GLuint model_ubo_index=glGetUniformBlockIndex(program->GetShader(),"Model");
      GLuint camera_ubo_index=glGetUniformBlockIndex(program->GetShader(),"Camera");
      GLuint material_ubo_index=glGetUniformBlockIndex(program->GetShader(),"Material");
      GLuint point_lights_ubo_index=glGetUniformBlockIndex(program->GetShader(),"PointLights");
      GLuint spot_lights_ubo_index=glGetUniformBlockIndex(program->GetShader(),"SpotLights");
      GLuint directional_lights_ubo_index=glGetUniformBlockIndex(program->GetShader(),"DirectionalLights");
      if(model_ubo_index!=GL_INVALID_INDEX)
      {
        glUniformBlockBinding(program->GetShader(),model_ubo_index,0);
        glBindBufferBase(GL_UNIFORM_BUFFER,0,m_model_matrix_ubo);
      }
      if(camera_ubo_index!=GL_INVALID_INDEX)
      {
        glUniformBlockBinding(program->GetShader(),camera_ubo_index,1);
        glBindBufferBase(GL_UNIFORM_BUFFER,1,m_control->GetCameraUBO());
      }
      if(point_lights_ubo_index!=GL_INVALID_INDEX)
      {
        glUniformBlockBinding(program->GetShader(),point_lights_ubo_index,2);
        glBindBufferBase(GL_UNIFORM_BUFFER,2,m_control->GetPointLightsUBO());
      }
      if(spot_lights_ubo_index!=GL_INVALID_INDEX)
      {
        glUniformBlockBinding(program->GetShader(),spot_lights_ubo_index,3);
        glBindBufferBase(GL_UNIFORM_BUFFER,3,m_control->GetSpotLightsUBO());
      }
      if(spot_lights_ubo_index!=GL_INVALID_INDEX)
      {
        glUniformBlockBinding(program->GetShader(),directional_lights_ubo_index,4);
        glBindBufferBase(GL_UNIFORM_BUFFER,4,m_control->GetDirectionalLightsUBO());
      }
      if(spot_lights_ubo_index!=GL_INVALID_INDEX)
      {
        glUniformBlockBinding(program->GetShader(),material_ubo_index,5);
        glBindBufferBase(GL_UNIFORM_BUFFER,5,nmaterial->GetUBO());
      }

      glUseProgram(program->GetShader());

      glBindVertexArray(nmesh->vao);
      if(pass->draw_mode==DrawMode::LINES)
        glDrawElementsInstanced(GL_LINES,mrc.mesh->GetIndices().size(),GL_UNSIGNED_INT,nullptr,mrc.transforms.size());
      else if(pass->draw_mode==DrawMode::NORMAL)
        glDrawElementsInstanced(GL_TRIANGLES,mrc.mesh->GetIndices().size(),GL_UNSIGNED_INT,nullptr,mrc.transforms.size());
      glBindVertexArray(0);
      //glUseProgram(0);

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
