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
  inline map<MaterialInfo*,GLuint>& GetVAOs(){return m_vao_map;}

  protected:
    void OnBindMaterial(MaterialInfo* mi)override;
    void OnClear()override;


  private:
    map<MaterialInfo*,GLuint> m_vao_map;
  };
}

#endif
