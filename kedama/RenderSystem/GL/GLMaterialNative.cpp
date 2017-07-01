#include "GLMaterialNative.hpp"

namespace Kedama {
  namespace GL
  {
    size_t GetUniformBlockSize(const list<AbstractPropertyValue> &property_list)//std140
    {
      size_t size=0;
      int count=0;

      for(auto it=property_list.begin();it!=property_list.end();++it)
      {
        switch(it->type)
        {
          case Material::Value::Type::TEXTURE:break;
          case Material::Value::Type::BOOL:
          case Material::Value::Type::INT:
          case Material::Value::Type::FLOAT:
            if(it->is_array)
            {
              size+=16*it->data.size();
            }
            else
            {
              ++it;
              if(it!=property_list.end()&&
                 it->type!=Material::Value::Type::VECTOR3&&
                 it->type!=Material::Value::Type::VECTOR4&&
                 it->type!=Material::Value::Type::MATRIX)
              {
                size+=4;
                count=(count==4?0:count+1);
              }
              else
                size+=(16-count*4);
              --it;
            }
            break;
          case Material::Value::Type::VECTOR3:
            size+=16*(it->data.size()/3);break;
          case Material::Value::Type::VECTOR4:
            size+=16*(it->data.size()/4);break;
          case Material::Value::Type::MATRIX:
            size+=16*(it->data.size()/16);break;
        }
      }
      return size;
    }

    GLMaterialNative::GLMaterialNative()
    {
    }

    GLMaterialNative::~GLMaterialNative()
    {
      glDeleteBuffers(1,&m_ubo);
    }

    void GLMaterialNative::Init(const list<AbstractPropertyValue> &property_list)
    {
      m_textures.clear();
      size_t size=GetUniformBlockSize(property_list);
      if(m_last_size!=size)
      {
        if(m_ubo!=0)
          glDeleteBuffers(1,&m_ubo);
        glCreateBuffers(1,&m_ubo);
        glNamedBufferStorage(m_ubo,size,nullptr,GL_MAP_WRITE_BIT);
        m_last_size=size;
      }
      uint8_t* ubo_mem=(uint8_t*)glMapNamedBufferRange(m_ubo,0,size,GL_MAP_WRITE_BIT);
      mat4* value_mat4;
      vec4* value_vec4;
      vec3* value_vec3;
      int offset=0;
      int count=0;

      for(auto it=property_list.begin();it!=property_list.end();++it)
      {
        switch(it->type)
        {
          case Material::Value::Type::TEXTURE:break;
          case Material::Value::Type::BOOL:
          case Material::Value::Type::INT:
          case Material::Value::Type::FLOAT:
            if(it->is_array)
            {
              for(int i=0;i<it->data.size();++i)
              {
                memcpy(ubo_mem+offset,&it->data[i],4);
                offset+=16;
              }
            }
            else
            {
              memcpy(ubo_mem+offset,&it->data[0],4);
              ++it;
              if(it!=property_list.end()&&
                 it->type!=Material::Value::Type::VECTOR3&&
                 it->type!=Material::Value::Type::VECTOR4&&
                 it->type!=Material::Value::Type::MATRIX)
              {
                offset+=4;
                count=(count==4?0:count+1);
              }
              else
              {
                offset+=(16-count*4);
                count=0;
              }
              --it;
            }
            break;

          case Material::Value::Type::VECTOR3:
            value_vec3=(vec3*)&it->data[0];
            for(int i=0;i<it->data.size()/3;++i)
            {
              memcpy(ubo_mem+offset,value_vec3++,12);
              offset+=16;
            }
            break;

          case Material::Value::Type::VECTOR4:
            value_vec4=(vec4*)&it->data[0];
            for(int i=0;i<it->data.size()/4;++i)
            {
              memcpy(ubo_mem+offset,value_vec4++,16);
              offset+=16;
            }
            break;

          case Material::Value::Type::MATRIX:
            value_mat4=(mat4*)&it->data[0];
            for(int i=0;i<it->data.size()/16;++i)
            {
              memcpy(ubo_mem+offset,value_mat4++,64);
              offset+=64;
            }
            break;
        }
      }
      glUnmapNamedBuffer(m_ubo);
    }
  }
}
