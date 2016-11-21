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
    vector<ITexture2DPtr> color;
    IRenderBufferPtr depth;
    IRenderBufferPtr depth_stencil;
  };
}

#endif
