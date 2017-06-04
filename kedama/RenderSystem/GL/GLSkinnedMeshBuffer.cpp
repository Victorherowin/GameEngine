//
// Created by moe on 2017-06-02.
//

#include "GLSkinnedMeshBuffer.hpp"

namespace Kedama {
    namespace GL {
        GLSkinnedMeshBuffer::GLSkinnedMeshBuffer(GLMeshBuffer* mesh_buffer):m_ibo(mesh_buffer->GetIBO()) {
        }
    }
}