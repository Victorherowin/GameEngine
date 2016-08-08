#ifndef GLRENDERSTREAM
#define GLRENDERSTREAM

#include "../RenderStream.hpp"
#include "../../Config.hpp"

namespace Kedama
{
  DEFINE_SHARED_PTR(GLRenderStream)

  class KEDAMA_API GLRenderStream:public RenderStream
  {
  public:
    ~GLRenderStream();
  inline map<const MeshInfo*,GLuint>& GetVAOs(){return m_vao_map;}

  protected:
    void OnBindMaterial(const MeshInfo* mi)override;
    void OnClear()override;


  private:
    map<const MeshInfo*,GLuint> m_vao_map;
  };
}

#endif
