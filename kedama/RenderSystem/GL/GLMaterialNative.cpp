#include "GLMaterialNative.hpp"

namespace Kedama {
  namespace GL
  {
    size_t GetUniformBlockSize(const list<Material::Value> &property_list)//std140
    {
      size_t size=0;
      for(const Material::Value& value:property_list)
      {
        switch(value.type)
        {
          case Material::Value::Type::TEXTURE:break;
          case Material::Value::Type::BOOL:
          case Material::Value::Type::INT:
          case Material::Value::Type::FLOAT:
            if(value.is_array)
            {
              size+=16*value.data.size();
            }
            else
            {
              size+=4;
            }
            break;
          case Material::Value::Type::VECTOR3:
            size+=16*value.data.size()/3;break;
          case Material::Value::Type::VECTOR4:
            size+=16*value.data.size()/4;break;
          case Material::Value::Type::MATRIX:
            size+=16*value.data.size()/16;break;
        }
      }
      return size;
    }

    GLMaterialNative::GLMaterialNative()
    {
      glCreateBuffers(1,&m_ubo);
    }

    GLMaterialNative::~GLMaterialNative()
    {
      glDeleteBuffers(1,&m_ubo);
    }

    void GLMaterialNative::Upload(const list<Material::Value> &property_list)
    {
      m_textures.clear();
      size_t size=GetUniformBlockSize(property_list);

      glNamedBufferStorage(m_ubo,size,nullptr,GL_MAP_WRITE_BIT);
      uint8_t* ubo_mem=(uint8_t*)glMapNamedBufferRange(m_ubo,0,size,GL_MAP_WRITE_BIT);
      vec4* tmp_vec4=(vec4*)ubo_mem;
      mat4* tmp_mat4=(mat4*)ubo_mem;
      mat4* value_mat4;
      vec4* value_vec4;
      vec3* value_vec3;

      for(const Material::Value& value:property_list)
      {
        switch(value.type)
        {
          case Material::Value::Type::TEXTURE:break;
          case Material::Value::Type::BOOL:
          case Material::Value::Type::INT:
          case Material::Value::Type::FLOAT:
            if(value.is_array)
            {
              vec4* tmp=(vec4*)ubo_mem;
              for(int i=0;i<value.data.size();++i)
                memcpy(&tmp++->x,&value.data[i],4);
              ubo_mem=(uint8_t*)tmp;
            }
            else
            {
              memcpy(ubo_mem,&value.data[0],4);
            }
            break;

          case Material::Value::Type::VECTOR3:
            tmp_vec4=(vec4*)ubo_mem;
            value_vec3=(vec3*)&value.data[0];
            for(int i=0;i<value.data.size()/3;++i)
              memcpy(tmp_vec4++,value_vec3++,12);
            ubo_mem=(uint8_t*)tmp_vec4;
            break;

          case Material::Value::Type::VECTOR4:
            tmp_vec4=(vec4*)ubo_mem;
            value_vec4=(vec4*)&value.data[0];
            for(int i=0;i<value.data.size()/4;++i)
              memcpy(tmp_vec4++,value_vec4++,16);
            ubo_mem=(uint8_t*)tmp_vec4;
            break;

          case Material::Value::Type::MATRIX:
            tmp_mat4=(mat4*)ubo_mem;
            value_mat4=(mat4*)&value.data[0];
            for(int i=0;i<value.data.size()/16;++i)
              memcpy(tmp_mat4++,value_mat4++,64);
            ubo_mem=(uint8_t*)tmp_mat4;
            break;
        }
      }
      glUnmapNamedBuffer(m_ubo);
    }
  }
}
