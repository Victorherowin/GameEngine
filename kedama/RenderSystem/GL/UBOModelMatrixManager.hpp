#ifndef UBOMODELMATRIXMANAGER
#define UBOMODELMATRIXMANAGER

#include "../../Include.hpp"
#include "../VertexBuffer.hpp"
#include "../Batch.hpp"

#define UBO_MAXSIZE 128

namespace Kedama {
  class UBOModelMatrixManager
  {
      struct weak_ptr_less{
        bool operator()(const weak_ptr<VertexBuffer>& x, const weak_ptr<VertexBuffer>& y)const
        { return x.lock() < y.lock(); }
      };
  public:

      GLuint GetUBO(Batch& batch)
      {
        if(m_manager.size()>100&&m_manager.size()%20==0)
          Clear();

        weak_ptr<VertexBuffer> wpvbo(batch.GetInstancies().front()->GetMeshes().front().mesh_buffer.first);
        if(m_manager.find(wpvbo)==m_manager.end())
          SetupUBO(batch);
        return m_manager[wpvbo];
      }

  private:
      inline void Clear()
      {
        for(auto it=m_manager.begin();it!=m_manager.end();++it)
        {
          if(it->first.expired())
          {
            glDeleteBuffers(1,&it->second);
            it=m_manager.erase(it);
          }
        }
      }

      inline void SetupUBO(Batch& batch)
      {
        GLuint ubo;
        glGenBuffers(1,&ubo);
        glNamedBufferData(ubo,sizeof(mat4)*UBO_MAXSIZE,nullptr,GL_DYNAMIC_DRAW);
        weak_ptr<VertexBuffer> wpvbo(batch.GetInstancies().front()->GetMeshes().front().mesh_buffer.first);
        int i=0;
        for(BaseModelPtr& bc:batch.GetInstancies())
        {
          bc->GetTansform().AddUpdateListener([i,ubo](Transform& tf)
          {
            glNamedBufferSubData(ubo,sizeof(mat4)*i,sizeof(mat4),glm::value_ptr(tf.GetModelMatrix()));
          });
          i++;
        }
        m_manager[wpvbo]=ubo;
      }
  private:
     map<const weak_ptr<VertexBuffer>,GLuint,weak_ptr_less> m_manager;
  };
}

#endif
