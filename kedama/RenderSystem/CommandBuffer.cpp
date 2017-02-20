#include "CommandBuffer.hpp"

namespace Kedama {

  void CommandBuffer::AddRenderCommand(Transform *transform, Mesh *mesh, Material *material)
  {
    RenderCommand rc;
    rc.transform=transform;
    rc.material=material;
    rc.mesh=mesh;

    m_commands.push_back(rc);
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
    map<pair<Mesh*,Material*>,MergedRenderCommand> merge_map;
    for(RenderCommand& rc:m_commands)
    {
      pair<Mesh*,Material*> tmp(rc.mesh,rc.material);
      auto it=merge_map.find(tmp);

      if(it==merge_map.end())
      {
        MergedRenderCommand mrc;
        mrc.material=rc.material;
        mrc.mesh=rc.mesh;
        mrc.transforms.push_back(rc.transform);
        merge_map[tmp]=mrc;
      }
      else
      {
        it->second.transforms.push_back(rc.transform);
      }
    }

    m_commands.clear();

    for(auto& p:merge_map)
    {
      if(p.second.transforms.size()==1)
      {
        RenderCommand rc;
        rc.transform=p.second.transforms[0];
        rc.mesh=p.second.mesh;
        rc.material=p.second.material;
        m_commands.push_back(rc);
      }
      else
      {
        m_merged_commands.push_back(p.second);
      }
    }
  }
}
