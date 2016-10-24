#ifndef RENDERSTREAM
#define RENDERSTREAM

#include "../Define.hpp"
#include "../Include.hpp"
#include "../GameObject/GameObject.hpp"

#include "VertexBuffer.hpp"
#include "IIndexBuffer.hpp"
#include "FrameBuffer.hpp"
#include "IShader.hpp"
#include "Material.hpp"
#include "Batch.hpp"

namespace Kedama
{
  DEFINE_SHARED_PTR(RenderStream)

  class KEDAMA_API RenderStream
  {
    public:
    virtual ~RenderStream(){}

    void AddBatch(const Batch& batch);
    inline const list<Batch> GetBatchs(){return m_batchs;}

    void Clear();

    protected:

    virtual void OnBindMaterial(const Batch& batch)=0;
    virtual void OnClear()=0;

    private:
    list<Batch> m_batchs;
  };
}

#endif
