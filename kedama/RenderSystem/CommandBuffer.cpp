#include "CommandBuffer.hpp"

namespace Kedama {
  void CommandBuffer::AddDeferredRenderCommand(Transform *transform, Mesh *mesh, Material *material)
  {
    RenderCommand rc;
    rc.transform=transform;
    rc.material=material;
    rc.mesh=mesh;

    m_deferred_commands.push_back(rc);
  }

  void CommandBuffer::AddForwardRenderCommand(Transform *transform, Mesh *mesh, Material *material)
  {
    RenderCommand rc;
    rc.transform=transform;
    rc.material=material;
    rc.mesh=mesh;

    m_forward_commands.push_back(rc);
  }

  void CommandBuffer::AddAlphaRenderCommand(Transform *transform, Mesh *mesh, Material *material)
  {
    RenderCommand rc;
    rc.transform=transform;
    rc.material=material;
    rc.mesh=mesh;

    m_alpha_forward_commands.push_back(rc);
  }

  void CommandBuffer::AddPostProcessCommand(Material *material)
  {
    PostProcessCommand ppc;
    ppc.material=material;

    m_post_process_commands.push_back(ppc);
  }

  void CommandBuffer::Sort(Camera* camera)
  {
    std::sort(m_alpha_forward_commands.begin(),m_alpha_forward_commands.end(),[camera]
    (const RenderCommand& a,const RenderCommand& b)
    {
      float a_len=glm::length(a.transform->GetWorldPosition()-camera->GetTansform()->GetWorldPosition());
      float b_len=glm::length(b.transform->GetWorldPosition()-camera->GetTansform()->GetWorldPosition());
      return a_len>b_len;
    });
  }

  void CommandBuffer::Merge()
  {
    //TODO:合并Command
  }
}
