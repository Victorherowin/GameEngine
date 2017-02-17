#include "GLMaterialNative.hpp"

namespace Kedama {
  namespace GL
  {
    size_t GetUniformBlockSize(const list<Material::Value> &property_list)//std140
    {
      size_t size=0;
      for(const Material::Value& value:property_list)
      {
        if(value.type==Material::Value::Type::TEXTURE)continue;
        if(value.type==Material::Value::Type::VECTOR3&&value.is_array==false)
          size+=4;
        size+=sizeof(GLfloat)*value.data.size();
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
      //TODO:Material UBO Block(std430,binding=0)
      m_textures.clear();
      size_t size=GetUniformBlockSize(property_list);

      glNamedBufferStorage(m_ubo,size,nullptr,GL_MAP_WRITE_BIT);
      uint8_t* ubo_mem=(uint8_t*)glMapNamedBufferRange(m_ubo,0,size,GL_MAP_WRITE_BIT);

      int offset=0;
      for(const Material::Value& value:property_list)
      {
        if(value.type!=Material::Value::Type::TEXTURE)
        {
          memcpy(ubo_mem+offset,value.data.data(),value.data.size()*4);
          if(value.type==Material::Value::Type::VECTOR3&&value.is_array==false)
            offset+=4;
          offset+=value.data.size()*4;
        }
        else
        {
          m_textures.push_back(make_pair(value.property_name,value._texture));
        }
      }
      glUnmapNamedBuffer(m_ubo);
    }
  }
}
