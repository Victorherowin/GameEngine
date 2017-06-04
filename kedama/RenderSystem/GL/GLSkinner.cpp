#include "GLSkinner.hpp"
#include "GL/glew.h"
#include "GLMeshBuffer.hpp"

#define JOINT_BINDING 0

namespace Kedama {
  namespace GL {
    //TODO:GPU蒙皮
    GLSkinner::GLSkinner(IMeshBuffer* mesh,Joint* joint):m_mesh(static_cast<GLMeshBuffer*>(mesh)),m_root_joint(joint),m_skinned_mesh(m_mesh)
    {
      CountJointNumber(m_root_joint);
      glCreateBuffers(1,&m_joint_ubo);
      glNamedBufferStorage(m_joint_ubo, sizeof(glm::dualquat)*m_joint_num, nullptr, GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);
      m_joint_ubo_map=(glm::dualquat*)glMapNamedBufferRange(m_joint_ubo, 0, sizeof(glm::dualquat)*m_joint_num, GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);
      ForeachAddListener(m_root_joint);

      //glUniformBlockBinding(m_shader,0,JOINT_BINDING);
    }

    GLSkinner::~GLSkinner()
    {
      ForeachDeleteListener(m_root_joint);
      glUnmapBuffer(m_joint_ubo);
      glDeleteBuffers(1,&m_joint_ubo);
    }

    void GLSkinner::ForeachAddListener(Joint *joint)
    {
      if(joint==nullptr)return;
      int i=m_joint_num;
      joint->AddUpdateListener("__glskinner_update__",[this,i](Transform& t)
      {
        memcpy(this->m_joint_ubo_map+i,&static_cast<Joint&>(t).GetWorldDualQuat()[0],sizeof(glm::dualquat));
      });

      for(auto j:joint->GetChildren())
        ForeachAddListener(static_cast<Joint*>(j));
    }

    void GLSkinner::ForeachDeleteListener(Joint *joint)
    {
      if(joint==nullptr)return;
      joint->RemoveUpdateListener("__glskinner_update__");
      for(auto j:joint->GetChildren())
        ForeachAddListener(static_cast<Joint*>(j));
    }

    void GLSkinner::CountJointNumber(Joint *joint)
    {
      if(joint==nullptr)return;
      ++m_joint_num;
      for(auto j:joint->GetChildren())
        CountJointNumber(static_cast<Joint*>(j));
    }

    void GLSkinner::Skinning()
    {
       //glBindBufferBase(GL_UNIFORM_BUFFER,JOINT_BINDING,m_joint_ubo);


    }

    IAbstractMeshBuffer* GLSkinner::GetSkinedMesh()
    {
      return &m_skinned_mesh;
    }
  }
}
