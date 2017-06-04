//
// Created by moe on 2017-06-02.
//

#ifndef KEDAMA_GLSKINNEDMESHBUFFER_HPP
#define KEDAMA_GLSKINNEDMESHBUFFER_HPP

#include "../Interface/IMeshBuffer.hpp"
#include "GLMeshBuffer.hpp"

namespace Kedama {
    namespace GL {
        class KEDAMA_API GLSkinnedMeshBuffer : public GLBaseMeshBuffer
        {
        public:
            GLSkinnedMeshBuffer(GLMeshBuffer* mesh_buffer);

        private:
            GLSharedBuffer m_ibo;
        };
    }
}

#endif //KEDAMA_GLSKINNEDMESHBUFFER_HPP
