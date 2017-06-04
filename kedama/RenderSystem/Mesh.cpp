#include "Mesh.hpp"
#include "../Engine.hpp"

namespace Kedama {
    StaticMesh::StaticMesh(size_t vertex_num,size_t index_num) {
        m_mesh_buff = Engine::GetSingleton().GetRendererFactory()->CreateMeshBuffer(vertex_num,index_num);
        m_mesh_buff->AddVertexAttribute("position",0,DataType::FLOAT,3,vertex_num*sizeof(vec3));
        m_mesh_buff->AddVertexAttribute("normal",1,DataType::FLOAT,3,vertex_num*sizeof(vec3));
        m_mesh_buff->AddVertexAttribute("uv",2,DataType::FLOAT,2,vertex_num*sizeof(vec2));
        m_mesh_buff->AddVertexAttribute("tangent",3,DataType::FLOAT,3,vertex_num*sizeof(vec3));
    }

    StaticMesh::~StaticMesh() {
        delete m_mesh_buff;
    }

    void StaticMesh::SetPositions(const vector<vec3> &pos) {
        m_positions = pos;
        m_mesh_buff->UpdateVertexAttribute("position",m_positions.data());
    }

    void StaticMesh::SetIndices(const vector<uint32_t> &indices) {
        m_indices = indices;
        m_mesh_buff->UpdateIndices(m_indices.data());
    }

    void StaticMesh::SetUVs(const vector<vec2> &uvs) {
        m_uvs = uvs;
        m_mesh_buff->UpdateVertexAttribute("uv",m_uvs.data());
    }

    void StaticMesh::SetNormals(const vector<vec3> &normals) {
        m_normals = normals;
        m_mesh_buff->UpdateVertexAttribute("normal",m_normals.data());
    }

    void StaticMesh::SetTangents(const vector<vec3> &tangent) {
        m_tangent = tangent;
        m_mesh_buff->UpdateVertexAttribute("tangent",m_tangent.data());
    }
}

namespace Kedama {
    SkinningMesh::SkinningMesh(size_t vertex_num,size_t index_num):StaticMesh(vertex_num,index_num)
    {
        m_mesh_buff->AddVertexAttribute("weight",4,DataType::FLOAT,4,vertex_num*sizeof(vec4));
        m_mesh_buff->AddVertexAttribute("weight_index",5,DataType::UINT,4,vertex_num*sizeof(uvec4));
    }

    void SkinningMesh::SetWeights(const vector<vec4> &weights)
    {
        m_weights = weights;
        m_mesh_buff->UpdateVertexAttribute("weight",m_weights.data());
    }

    void SkinningMesh::SetBoneIndices(const vector<uvec4> &bone_indices) {
        m_bone_indices = bone_indices;
        m_mesh_buff->UpdateVertexAttribute("weight_index",m_bone_indices.data());
    }
}
