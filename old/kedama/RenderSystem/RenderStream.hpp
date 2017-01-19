#ifndef RENDERSTREAM
#define RENDERSTREAM

#include "../Define.hpp"
#include "../Include.hpp"
#include "../GameObject/GameObject.hpp"

#include "VertexBuffer.hpp"
#include "IIndexBuffer.hpp"
#include "FrameBuffer.hpp"
#include "Shader.hpp"
#include "Material.hpp"
#include "Batch.hpp"

namespace Kedama
{
  class KEDAMA_API RenderStream
  {
    public:
    virtual ~RenderStream(){}

    inline bool Empty()
    {return m_batch_queue.empty();}

    inline void AddBatch(const Batch& batch)
    {m_batch_queue.push(batch);}

    inline void PopBatch()
    {
      m_batch_queue.pop();
    }

    inline const Batch GetBatch()
    {
      return m_batch_queue.front();
    }

    inline uint32_t GetSize()
    {return m_batch_queue.size();}


    private:
    queue<Batch> m_batch_queue;
  };
}

#endif
