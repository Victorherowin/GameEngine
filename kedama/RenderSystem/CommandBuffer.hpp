#ifndef _H_COMMANDBUFFER
#define _H_COMMANDBUFFER

#include "../Include.hpp"
#include "RenderCommand.hpp"
#include "../GameObject/Camera.hpp"

namespace Kedama {
  using namespace std;

  class KEDAMA_API CommandBuffer
  {
  private:

    vector<RenderCommand> m_commands;
    vector<RenderCommand> m_alpha_forward_commands;

    //同一mesh command合并后
    vector<MergedRenderCommand> m_merged_commands;
    vector<PostProcessCommand> m_post_process_commands;
  public:
    void AddRenderCommand(Transform* transform,Mesh* mesh,Material* material);
    void AddAlphaRenderCommand(Transform* transform,Mesh* mesh,Material* material);
    void AddPostProcessCommand(PostProcessMaterial* material);

    //排序m_alpha_forward_command
    void Sort(Camera* camera);
    //合并相同Mesh
    void Merge();

    inline const vector<RenderCommand>& GetCommands()const
    {return m_commands;}

    inline const vector<RenderCommand>& GetAlphaForwardCommands()const
    {return m_alpha_forward_commands;}

    inline const vector<MergedRenderCommand>& GetMergedRenderCommands()const
    {return m_merged_commands;}

    inline const vector<PostProcessCommand>& GetPostProcessCommands()const
    {return m_post_process_commands;}
  };
}

#endif
