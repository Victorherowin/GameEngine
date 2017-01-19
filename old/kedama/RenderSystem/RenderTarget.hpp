#ifndef RENDERTARGET
#define RENDERTARGET

#include "../Include.hpp"
#include "../Define.hpp"

#include "ITexture2D.hpp"
#include "IRenderBuffer.hpp"

namespace Kedama {
  using namespace std;

  struct RenderTarget
  {
    vector<ITexture2D*> color;
    IRenderBuffer* depth;
    IRenderBuffer* depth_stencil;
  };
}

#endif
