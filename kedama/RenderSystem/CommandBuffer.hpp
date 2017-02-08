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
    //启用延迟渲染时此前向渲染队列缓存透明物体RenderCommand，并会在排序后渲染
    vector<RenderCommand> m_forward_commands;
    vector<RenderCommand> m_deferred_commands;
    vector<RenderCommand> m_alpha_forward_commands;

    //同一mesh command合并后
    vector<MergedRenderCommand> m_merged_commands;
    vector<PostProcessCommand> m_post_process_commands;
  public:
    void AddForwardRenderCommand(Transform* transform,Mesh* mesh,Material* material);
    void AddDeferredRenderCommand(Transform* transform,Mesh* mesh,Material* material);
    void AddAlphaRenderCommand(Transform* transform,Mesh* mesh,Material* material);
    void AddPostProcessCommand(Material* material);

    //排序m_alpha_forward_command
    void Sort(Camera* camera);
    //合并相同Mesh
    void Merge();

    inline const vector<RenderCommand>& GetForwardCommands()const
    {return m_forward_commands;}

    inline const vector<RenderCommand>& GetDeferredCommands()const
    {return m_deferred_commands;}

    inline const vector<RenderCommand>& GetAlphaForwardCommands()const
    {return m_alpha_forward_commands;}

    inline const vector<MergedRenderCommand>& GetMergedRenderCommans()const
    {return m_merged_commands;}

    inline const vector<PostProcessCommand>& GetPostProcessCommands()const
    {return m_post_process_commands;}
  };
}

#endif
