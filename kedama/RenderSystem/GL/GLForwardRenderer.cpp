#include "GLForwardRenderer.hpp"
#include "GLTexture2D.hpp"
#include "GLMeshNative.hpp"
#include "GLMaterialNative.hpp"
#include "GLShader.hpp"
#include "GLControl.hpp"
#include "GLLightNative.hpp"
#include "Shader/ForwardRenderDefaultShader.hpp"

#define MODEL_MATRIX_INDEX 4

namespace Kedama {
  namespace GL {
    GLForwardRenderer::GLForwardRenderer(GLControl* control):m_control(control)
    {
      glCreateBuffers(1,&m_model_matrix_ubo);
      glNamedBufferStorage(m_model_matrix_ubo,sizeof(mat4)*1000,nullptr,GL_MAP_WRITE_BIT|GL_MAP_PERSISTENT_BIT|GL_MAP_COHERENT_BIT);
      m_model_matrix_ubo_data=(mat4*)glMapNamedBufferRange(m_model_matrix_ubo,0,sizeof(mat4)*1000,GL_MAP_WRITE_BIT|GL_MAP_PERSISTENT_BIT|GL_MAP_COHERENT_BIT);

      m_default_shader.SetVertexShaderSource(default_vs_shader);
      m_default_shader.SetFragmentShaderSource(default_fs_shader);
      m_default_shader.Compile();
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
      GLShader* program=&m_default_shader;;
      if(pass->shader!=nullptr)
      {
        program=static_cast<GLShader*>(pass->shader);
      }


      mat4* i=m_model_matrix_ubo_data;
      for(Transform* t:mrc.transforms)
      {
        memcpy(i,glm::value_ptr(t->GetModelMatrix()),sizeof(mat4));
        ++i;
      }

      glBindBufferBase(GL_UNIFORM_BUFFER,MODEL_BINDING,m_model_matrix_ubo);
      glBindBufferBase(GL_UNIFORM_BUFFER,CAMERA_BINDING,m_control->GetCameraUBO());
      glBindBufferBase(GL_UNIFORM_BUFFER,MATERIAL_BINDING,nmaterial->GetUBO());

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

      glUseProgram(program->GetShader());

      glBindVertexArray(nmesh->vao);

      if (m_control->GetLights().size() != 0)
      {
        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ONE);
        for (Light* light : m_control->GetLights())
        {
          GLLightNative* gln = static_cast<GLLightNative*>(light->GetNative());
          glBindBufferBase(GL_UNIFORM_BUFFER, LIGHTS_BINDING, gln->GetUBO());
          if(pass->draw_mode == DrawMode::POINT)
            glDrawArraysInstanced(GL_POINTS,0,mrc.mesh->GetVertices().size(),mrc.transforms.size());
          else if (pass->draw_mode == DrawMode::LINES)
            glDrawElementsInstanced(GL_LINES,mrc.mesh->GetIndices().size(), GL_UNSIGNED_INT,0, mrc.transforms.size());
          else
            glDrawElementsInstanced(GL_TRIANGLES, mrc.mesh->GetIndices().size(), GL_UNSIGNED_INT, 0, mrc.transforms.size());
        }
        glDisable(GL_BLEND);
      }
      else
      {
        if(pass->draw_mode == DrawMode::POINT)
          glDrawArraysInstanced(GL_POINTS,0,mrc.mesh->GetVertices().size(),mrc.transforms.size());
        else if (pass->draw_mode == DrawMode::LINES)
          glDrawElementsInstanced(GL_LINES, mrc.mesh->GetIndices().size(), GL_UNSIGNED_INT, 0, mrc.transforms.size());
        else
          glDrawElementsInstanced(GL_TRIANGLES, mrc.mesh->GetIndices().size(), GL_UNSIGNED_INT, 0, mrc.transforms.size());
      }
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
