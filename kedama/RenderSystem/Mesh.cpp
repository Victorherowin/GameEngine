#include "Mesh.hpp"
#include "../Engine.hpp"

namespace Kedama {
    StaticMesh::StaticMesh(size_t vertices_num,size_t indices_num=0):m_vertices_num(vertices_num),m_indices_num(indices_num) {
        m_mesh_buff = Engine::GetSingleton().GetRendererFactory()->CreateMeshBuffer(vertices_num,indices_num);
    }

    StaticMesh::~StaticMesh() {
        delete m_mesh_buff;
    }

    void StaticMesh::SetPositions(const vector<vec3> &pos) {
        if(!(m_flag&0b1))
        {
            m_mesh_buff->AddVertexAttribute("position",0,DataType::FLOAT,3,m_vertices_num*sizeof(vec3));
            m_flag|=0b1;
        }
        m_positions = pos;
        m_mesh_buff->UpdateVertexAttribute("position",m_positions.data());
    }

    void StaticMesh::SetNormals(const vector<vec3> &normals) {
        if(!(m_flag&0b10))
        {
            m_mesh_buff->AddVertexAttribute("normal",1,DataType::FLOAT,3,m_vertices_num*sizeof(vec3));
            m_flag|=0b10;
        }
        m_normals = normals;
        m_mesh_buff->UpdateVertexAttribute("normal",m_normals.data());
    }

    void StaticMesh::SetUVs(const vector<vec2> &uvs) {
        if(!(m_flag&0b100))
        {
            m_mesh_buff->AddVertexAttribute("uv",2,DataType::FLOAT,2,m_vertices_num*sizeof(vec2));
            m_flag|=0b100;
        }
        m_uvs = uvs;
        m_mesh_buff->UpdateVertexAttribute("uv",m_uvs.data());
    }

    void StaticMesh::SetTangents(const vector<vec3> &tangent) {
        if(!(m_flag&0b1000))
        {
            m_mesh_buff->AddVertexAttribute("tangent",3,DataType::FLOAT,3,m_vertices_num*sizeof(vec3));
            m_flag|=0b1000;
        }
        m_tangent = tangent;
        m_mesh_buff->UpdateVertexAttribute("tangent",m_tangent.data());
    }

    void StaticMesh::SetIndices(const vector<uint32_t> &indices) {
        if(m_indices_num==0)
            throw invalid_argument("Indices Number is 0");
        m_indices = indices;
        m_mesh_buff->UpdateIndices(m_indices.data());
    }
}

namespace Kedama {
    SkinningMesh::SkinningMesh(size_t vertex_num,size_t index_num):StaticMesh(vertex_num,index_num) {
    }

    void SkinningMesh::SetBoneWeights(const vector<vec4> &weights) {
        if(!(m_flag&0b10000))
        {
            m_mesh_buff->AddVertexAttribute("bone_weight",4,DataType::FLOAT,4,m_vertices_num*sizeof(vec4));
            m_flag|=0b10000;
        }
        m_bone_weights = weights;
        m_mesh_buff->UpdateVertexAttribute("bone_weight",m_bone_weights.data());
    }

    void SkinningMesh::SetBoneIndices(const vector<uvec4> &bone_indices) {
        if(!(m_flag&0b100000))
        {
            m_mesh_buff->AddVertexAttribute("bone_index",5,DataType::UINT,4,m_vertices_num*sizeof(uvec4));
            m_flag|=0b100000;
        }
        m_bone_indices = bone_indices;
        m_mesh_buff->UpdateVertexAttribute("bone_index",m_bone_indices.data());
    }
}
