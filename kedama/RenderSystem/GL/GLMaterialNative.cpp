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
          case Material::Value::Type::COLOR://4*4
          case Material::Value::Type::MATRIX://16*4
            size+=16*value.data.size()/4;
            break;
          case Material::Value::Type::FLOAT://4
          case Material::Value::Type::INT:
            size+=16*value.data.size();
            break;

        }
      }
      return size;
    }

    GLMaterialNative::GLMaterialNative()
    {
      glGenBuffers(1,&m_ubo);
    }

    GLMaterialNative::~GLMaterialNative()
    {
      glDeleteBuffers(1,&m_ubo);
    }

    void GLMaterialNative::Upload(const list<Material::Value> &property_list)
    {
      //TODO:Material UBO Block(std430,binding=0)
      m_textures.clear();
      size_t size=GetUniformBlockSize(property_list);

      glNamedBufferData(m_ubo,size*4,nullptr,GL_STATIC_DRAW);
      uint8_t* ubo_mem=(uint8_t*)glMapNamedBuffer(m_ubo,GL_WRITE_ONLY);

      int offset=0;
      for(const Material::Value& value:property_list)
      {
        switch(value.type)
        {
          case Material::Value::Type::TEXTURE:
            m_textures.push_back(make_pair(value.property_name,value._texture));
            break;
          case Material::Value::Type::MATRIX:
          case Material::Value::Type::COLOR:
            memcpy(ubo_mem+offset,value.data.data(),value.data.size()*4);
            offset+=value.data.size()*4;
            break;
          case Material::Value::Type::FLOAT:
          case Material::Value::Type::INT:
            for(auto& obj:value.data)
            {
              memcpy(ubo_mem+offset,&obj,4);
              offset+=16;
            }
            break;
        }
      }
      glUnmapNamedBuffer(m_ubo);
    }
  }
}
