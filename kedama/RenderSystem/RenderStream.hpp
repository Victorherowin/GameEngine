#ifndef RENDERSTREAM
#define RENDERSTREAM

#include "../Config.hpp"
#include "VertexBuffer.hpp"
#include "IIndexBuffer.hpp"
#include "FrameBuffer.hpp"
#include "IShader.hpp"
#include "Material.hpp"

namespace Kedama
{
  DEFINE_SHARED_PTR(RenderStream)

  class KEDAMA_API RenderStream
  {
    public:
    using MeshBuffer=pair<VertexBufferPtr,IIndexBufferPtr>;

    struct MaterialInfo
    {
      MeshBuffer& mesh_buffer;
      uint32_t offset;
      uint32_t vertex_size;

      MaterialPtr material;
    };

    public:
    virtual ~RenderStream(){}
    uint32_t AddMeshBuffer(const MeshBuffer& mb);
    void BindMaterial(uint32_t mesh_id,MaterialPtr& material,uint32_t offset,uint32_t size);

    void Clear();

    inline vector<MaterialInfo>& GetDrawInfo(){return m_texs;}

    protected:

    virtual void OnBindMaterial(MaterialInfo* mi)=0;
    virtual void OnClear()=0;

    private:
    vector<MeshBuffer> m_meshbuffers;
    vector<MaterialInfo> m_texs;
  };
}

#endif
