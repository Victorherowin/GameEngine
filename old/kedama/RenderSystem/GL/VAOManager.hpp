#ifndef VAOMANAGER
#define VAOMANAGER

#include "GLVertexBuffer.hpp"
#include "GLIndexBuffer.hpp"

#include "../Mesh.hpp"
#include "UBOModelMatrixManager.hpp"

namespace Kedama {

  class VAOManager{
    struct weak_ptr_less{
      bool operator()(const weak_ptr<VertexBuffer>& x, const weak_ptr<VertexBuffer>& y)const
      { return x.lock() < y.lock(); }
    };

  public:
    GLuint GetVAO(const Mesh& mesh,Batch& batch)
    {
      if(m_manager.size()>100&&m_manager.size()%20==0)
        Clear();

      weak_ptr<VertexBuffer> wpvbo(mesh.mesh_buffer.first);
      if(m_manager.find(wpvbo)==m_manager.end())
      {
        SetupVAO(mesh,batch);
      }
      return m_manager[wpvbo];
    }

    ~VAOManager()
    {
      for(auto& obj:m_manager)
      {
        glDeleteVertexArrays(1,&obj.second);
      }
    }

  private:
    inline void Clear()
    {
      for(auto it=m_manager.begin();it!=m_manager.end();++it)
      {
        if(it->first.expired())
        {
          glDeleteVertexArrays(1,&it->second);
          it=m_manager.erase(it);
        }
      }
    }

    inline void SetupVAO(const Mesh& mesh,Batch& batch)
    {
      static GLenum __format_table[]={GL_INT,GL_SHORT,GL_BYTE,GL_UNSIGNED_INT,GL_UNSIGNED_SHORT,GL_UNSIGNED_BYTE,
                                      GL_FLOAT,GL_HALF_FLOAT,GL_INT_2_10_10_10_REV,GL_UNSIGNED_INT_2_10_10_10_REV,
                                      GL_UNSIGNED_INT_10F_11F_11F_REV};

      weak_ptr<VertexBuffer> wpvbo(mesh.mesh_buffer.first);
      GLuint vao;
      glGenVertexArrays(1,&vao);
      m_manager[wpvbo]=vao;

      GLVertexBufferPtr spvbo=std::static_pointer_cast<GLVertexBuffer>(mesh.mesh_buffer.first);
      GLIndexBufferPtr spibo=std::static_pointer_cast<GLIndexBuffer>(mesh.mesh_buffer.second);
      const VertexLayout& vl=spvbo->GetVertexLayout();

      GLuint mmubo=m_ubo_mm_manager.GetUBO(batch);

      glBindVertexArray(vao);
      spvbo->Bind();
      spibo->Bind();

      glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(GLVertex),(const void*)(offsetof(GLVertex,m_position)+mesh.offset));
      glVertexAttribPointer(1,2,GL_UNSIGNED_SHORT,GL_TRUE,sizeof(GLVertex),(const void*)(offsetof(GLVertex,m_uv)+mesh.offset));
      glVertexAttribPointer(2,3,GL_SHORT,GL_TRUE,sizeof(GLVertex),(const void*)(offsetof(GLVertex,m_normal)+mesh.offset));
      glVertexAttribPointer(3,4,GL_SHORT,GL_TRUE,sizeof(GLVertex),(const void*)(offsetof(GLVertex,m_tbn_quat)+mesh.offset));
      glVertexAttribPointer(4,4,GL_UNSIGNED_SHORT,GL_TRUE,sizeof(GLVertex),(const void*)(offsetof(GLVertex,m_bone_index)+mesh.offset));
      glVertexAttribPointer(5,4,GL_UNSIGNED_BYTE,GL_TRUE,sizeof(GLVertex),(const void*)(offsetof(GLVertex,m_weight)+mesh.offset));
      glEnableVertexAttribArray(0);
      glEnableVertexAttribArray(1);
      glEnableVertexAttribArray(2);
      glEnableVertexAttribArray(3);
      glEnableVertexAttribArray(4);
      glEnableVertexAttribArray(5);

      glBindBuffer(GL_ARRAY_BUFFER,mmubo);
      glVertexAttribPointer(6,4,GL_FLOAT,GL_FALSE,sizeof(mat4),(const void*)0);
      glVertexAttribPointer(7,4,GL_FLOAT,GL_FALSE,sizeof(mat4),(const void*)16);
      glVertexAttribPointer(8,4,GL_FLOAT,GL_FALSE,sizeof(mat4),(const void*)32);
      glVertexAttribPointer(9,4,GL_FLOAT,GL_FALSE,sizeof(mat4),(const void*)48);
      glEnableVertexAttribArray(6);
      glEnableVertexAttribArray(7);
      glEnableVertexAttribArray(8);
      glEnableVertexAttribArray(9);
      glVertexAttribDivisor(6,1);
      glVertexAttribDivisor(7,1);
      glVertexAttribDivisor(8,1);
      glVertexAttribDivisor(9,1);
      glBindBuffer(GL_ARRAY_BUFFER,0);

      if(!vl.layout.empty())
      {
        for(auto p:vl.layout)
        {
          if(p.first<=9)throw runtime_error("Index Need >9");
          glVertexAttribPointer(p.first,(GLint)p.second.size,__format_table[(int32_t)p.second.type],
              p.second.normalized, p.second.stride,(const void*)(p.second.offset+mesh.offset));
          glEnableVertexAttribArray(p.first);
        }
      }

      glBindVertexArray(0);
    }

  private:
    map<weak_ptr<VertexBuffer>,GLuint,weak_ptr_less> m_manager;
    UBOModelMatrixManager m_ubo_mm_manager;
  };
}

#endif
