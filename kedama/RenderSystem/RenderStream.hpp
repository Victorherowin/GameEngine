#ifndef RENDERSTREAM
#define RENDERSTREAM

#include "../Config.hpp"
#include "IVertexBuffer.hpp"
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

    using MeshBuffer = pair<IVertexBufferPtr,IIndexBufferPtr>;

    struct MaterialInfo
    {
      MeshBuffer mb;
      uint32_t offset;
      uint32_t vertex_size;

      MaterialPtr tex;
    };

    public:
    uint32_t AddMeshBuffer(MeshBuffer mb);
    void BindMaterial(uint32_t mesh_id,MaterialPtr& tex,uint32_t offset,uint32_t size);

    void Clear();

    inline vector<MaterialInfo>& GetDrawInfo()
    {
      return m_texs;
    }

    static RenderStreamPtr CreateRenderStream();

    vector<MeshBuffer> m_meshbuffers;
    vector<MaterialInfo> m_texs;

  };
}

#endif
