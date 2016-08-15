#ifndef RENDERSTREAM
#define RENDERSTREAM

#include "../Config.hpp"
#include "VertexBuffer.hpp"
#include "IIndexBuffer.hpp"
#include "FrameBuffer.hpp"
#include "IShader.hpp"
#include "Material.hpp"
#include "../GameObject/GameObject.hpp"

namespace Kedama
{
  DEFINE_SHARED_PTR(RenderStream)

  class KEDAMA_API RenderStream
  {
    public:
    using MeshBuffer=pair<VertexBufferPtr,IIndexBufferPtr>;

    class KEDAMA_API InstancingInfo
    {
    public:
      uint32_t AddInstance(Transform& tf)
      {
        m_transform_ptrs.push_back(&tf);
        return m_transform_ptrs.end()-m_transform_ptrs.begin()-1;
      }
      Transform* GetTransformPtr(uint32_t id){return m_transform_ptrs[id];}
      inline bool Empty(){return m_transform_ptrs.empty();}
      inline uint32_t GetSize(){return m_transform_ptrs.size();}

    private:
      vector<Transform*> m_transform_ptrs;
    };

    struct MeshInfo
    {
      MeshBuffer& mesh_buffer;
      uint32_t offset;
      MaterialPtr material;
      InstancingInfo m_instancing_info;
    };

    public:
    virtual ~RenderStream(){}

    uint32_t AddMeshBuffer(const MeshBuffer& mb);
    void BindMaterial(uint32_t mesh_id,MaterialPtr& material,uint32_t offset);
    inline InstancingInfo& GetInstancingInfoRef(uint32_t mesh_id){return m_mesh_info[mesh_id].m_instancing_info;}

    void Clear();

    inline vector<MeshInfo>& GetDrawInfo(){return m_mesh_info;}

    protected:

    virtual void OnBindMaterial(const MeshInfo* mi)=0;
    virtual void OnClear()=0;

    private:
    vector<MeshBuffer> m_meshbuffers;
    vector<MeshInfo> m_mesh_info;
  };
}

#endif
