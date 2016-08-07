#include "GLTextureBase.hpp"

namespace Kedama {
  GLTextureBase::GLTextureBase()
  {
    glGenTextures(1,&m_tex);
  }

  GLTextureBase::~GLTextureBase()
  {
    glDeleteTextures(1,&m_tex);
  }

  void GLTextureBase::GenerateMipmap()
  {
    glGenerateMipmap(m_tex);
  }
}
