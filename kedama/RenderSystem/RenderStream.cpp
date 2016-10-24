#include "RenderStream.hpp"

namespace Kedama
{
  void RenderStream::AddBatch(const Batch& batch)
  {
    m_batchs.push_back(batch);
    OnBindMaterial(m_batchs.back());
  }

  void RenderStream::Clear()
  {
    m_batchs.clear();
    OnClear();
  }
}
