#ifndef _H_MESH
#define _H_MESH

#include "../Define.hpp"
#include "../Include.hpp"
#include "../GLMInclude.hpp"
#include "Material.hpp"
#include "Interface/IMeshBuffer.hpp"

namespace Kedama {
    using namespace glm;
    using namespace std;

    class KEDAMA_API StaticMesh {
    public:
        StaticMesh(size_t vertex_num,size_t index_num);

        virtual ~StaticMesh();

        void SetPositions(const vector<vec3> &positions);
        void SetNormals(const vector<vec3> &normals);
        void SetUVs(const vector<vec2> &uvs);
        void SetTangents(const vector<vec3> &tangent);

        void SetIndices(const vector<uint32_t> &indices);

        inline const vector<vec3> &GetPositions() const { return m_positions; }
        inline const vector<vec3> &GetNormals() const { return m_normals; }
        inline const vector<vec2> &GetUVs() const { return m_uvs; }
        inline const vector<vec3> &GetTangents() const { return m_tangent; }

        inline const vector<uint32_t> &GetIndices() const { return m_indices; }

        inline const IAbstractMeshBuffer* GetMeshBuffer()const{return m_mesh_buff;}

    private:
        vector<vec2> m_uvs;
        vector<vec3> m_positions;
        vector<vec3> m_normals;
        vector<vec3> m_tangent;
        vector<uint32_t> m_indices;
    protected:
        IMeshBuffer *m_mesh_buff=nullptr;
        uint32_t m_vertices_num=0,m_indices_num=0;
        uint8_t m_flag=0;
    };
}


namespace Kedama {
    class KEDAMA_API SkinningMesh : public StaticMesh {
    public:
        SkinningMesh(size_t vertex_num,size_t index_num);

        void SetBoneWeights(const vector<vec4> &weights);
        void SetBoneIndices(const vector<uvec4> &bone_indices);

        inline const vector<vec4> &GetWeights() const { return m_bone_weights; }
        inline const vector<uvec4> &GetBoneIndices() const { return m_bone_indices; }

    protected:
        vector<vec4> m_bone_weights;
        vector<uvec4> m_bone_indices;
    };
}

#endif
