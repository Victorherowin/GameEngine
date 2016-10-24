#ifndef GLRENDERSTREAM
#define GLRENDERSTREAM

#include "../RenderStream.hpp"
#include "../../Include.hpp"
#include "../../Define.hpp"

namespace Kedama
{
  DEFINE_SHARED_PTR(GLRenderStream)

  class KEDAMA_API GLRenderStream:public RenderStream
  {
  public:
    ~GLRenderStream();
    inline map<const Mesh*,GLuint>& GetVAOs(){return m_vao_map;}

  protected:
    void OnBindMaterial(const Batch& mi)override;
    void OnClear()override;


  private:
    map<const Mesh*,GLuint> m_vao_map;
  };
}

#endif
