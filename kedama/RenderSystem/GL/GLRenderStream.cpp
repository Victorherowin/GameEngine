#include "GLRenderStream.hpp"

#include "GLIndexBuffer.hpp"
#include "GLVertexBuffer.hpp"

namespace Kedama
{
  void GLRenderStream::OnBindMaterial(MaterialInfo* mi)
  {
    static GLenum __format_table[]={GL_INT,GL_INT16_NV,GL_INT8_NV,GL_UNSIGNED_INT,GL_UNSIGNED_INT16_NV,GL_UNSIGNED_INT8_NV,
                                    GL_FLOAT,GL_HALF_FLOAT};

    static VertexLayout __vl({0,1,2,3,4,5});

    GLuint vao;
    glGenVertexArrays(1,&vao);
    m_vao_map[mi]=vao;

    GLVertexBufferPtr vboptr=std::dynamic_pointer_cast<GLVertexBuffer>(mi->mesh_buffer.first);
    GLIndexBufferPtr iboptr=std::dynamic_pointer_cast<GLIndexBuffer>(mi->mesh_buffer.second);

    VertexLayout& vl=__vl;

    glBindVertexArray(vao);
    vboptr->Bind();
    iboptr->Bind();
    if(vboptr->UseVertexLayout())
    {
      vl=vboptr->GetVertexLayout();
    }

    if(vl.position!=VertexLayout::UNUSEED)
    {
      glVertexAttribPointer(vl.position,3,GL_FLOAT,GL_FALSE,sizeof(GLVertex),(const void*)offsetof(GLVertex,m_position));
      glEnableVertexAttribArray(vl.position);
    }
    if(vl.normal!=VertexLayout::UNUSEED)
    {
      glVertexAttribPointer(vl.normal,3,GL_INT16_NV,GL_TRUE,sizeof(GLVertex),(const void*)offsetof(GLVertex,m_normal));
      glEnableVertexAttribArray(vl.normal);
    }
    if(vl.coord!=VertexLayout::UNUSEED)
    {
      glVertexAttribPointer(vl.coord,2,GL_UNSIGNED_INT16_NV,GL_TRUE,sizeof(GLVertex),(const void*)offsetof(GLVertex,m_uv));
      glEnableVertexAttribArray(vl.coord);
    }
    if(vl.tbn!=VertexLayout::UNUSEED)
    {
      glVertexAttribPointer(vl.tbn,4,GL_INT16_NV,GL_TRUE,sizeof(GLVertex),(const void*)offsetof(GLVertex,m_tbn_quat));
      glEnableVertexAttribArray(vl.tbn);
    }if(vl.bone_index!=VertexLayout::UNUSEED)
    {
      glVertexAttribPointer(vl.bone_index,4,GL_UNSIGNED_INT16_NV,GL_TRUE,sizeof(GLVertex),(const void*)offsetof(GLVertex,m_bone_index));
      glEnableVertexAttribArray(vl.bone_index);
    }
    if(vl.weight!=VertexLayout::UNUSEED)
    {
      glVertexAttribPointer(vl.weight,4,GL_UNSIGNED_INT8_NV,GL_TRUE,sizeof(GLVertex),(const void*)offsetof(GLVertex,m_weight));
      glEnableVertexAttribArray(vl.weight);
    }
    if(vl.custom.size()>0)
    {
      for(auto& vle:vl.custom)
      {
        glVertexAttribPointer(std::get<5>(vle),std::get<1>(vle),__format_table[(int)std::get<0>(vle)],GL_FALSE,std::get<3>(vle),(const void*)std::get<4>(vle));
        glEnableVertexAttribArray(std::get<5>(vle));
      }
    }

    glBindVertexArray(0);
  }

  void GLRenderStream::OnClear()
  {
    for(auto& pair:m_vao_map)
    {
      glDeleteVertexArrays(1,&pair.second);
    }
    m_vao_map.clear();
  }

  GLRenderStream::~GLRenderStream()
  {
    OnClear();
  }

}
