#ifndef _H_GLSKINNER
#define _H_GLSKINNER

#include "../../BoneSystem/ISkinner.hpp"
#include "../../BoneSystem/Joint.hpp"
#include "../../RenderSystem/Mesh.hpp"
#include "GLMeshBuffer.hpp"
#include "GLSkinnedMeshBuffer.hpp"

namespace Kedama {
  namespace GL {
    class GLSkinner:public ISkinner
    {
    public:
      GLSkinner(IMeshBuffer* mesh,Joint* joint);
      ~GLSkinner();
      void Skinning()override final;
      IAbstractMeshBuffer* GetSkinedMesh()override final;

    private:
      void ForeachAddListener(Joint* joint);
      void ForeachDeleteListener(Joint* joint);
      void CountJointNumber(Joint* joint);
    private:
      GLuint m_joint_ubo=0;
      glm::dualquat* m_joint_ubo_map=nullptr;
      size_t m_joint_num=0;

      Joint* m_root_joint=nullptr;
      GLMeshBuffer* m_mesh=nullptr;
      GLSkinnedMeshBuffer m_skinned_mesh;
    };
  }
}

#endif
