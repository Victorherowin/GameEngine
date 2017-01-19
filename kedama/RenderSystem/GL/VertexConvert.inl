#include "../../Include.hpp"
#include "../Mesh.hpp"

namespace Kedama {
  namespace GL {
    using namespace std;
    using namespace glm;
    class VertexConverter
    {
    public:
      VertexConverter(Mesh* mesh):m_mesh(mesh){}

      pair<vec3,vec3> GetBoundSize()
      {
        m_bound_box=make_pair(m_mesh->GetVertices()[0],m_mesh->GetVertices()[0]);
        m_is_call_getboundsize=false;

        if(!m_is_call_getboundsize)
          for(auto v:m_mesh->GetVertices())
          {
            m_bound_box.first.x=std::min(v.x,m_bound_box.first.x);
            m_bound_box.first.y=std::min(v.y,m_bound_box.first.y);
            m_bound_box.first.z=std::min(v.x,m_bound_box.first.z);
            m_bound_box.second.x=std::max(v.x,m_bound_box.second.x);
            m_bound_box.second.y=std::max(v.y,m_bound_box.second.y);
            m_bound_box.second.z=std::max(v.x,m_bound_box.second.z);
          }

        m_is_call_getboundsize=true;
        return m_bound_box;
      }

      vector<u16vec3> GetVertices()
      {
        vector<u16vec3> vert;
        u16vec3 tmp;
        for(auto v:m_mesh->GetVertices())
        {
          tmp=(v+m_bound_box.first)/glm::length(m_bound_box.second-m_bound_box.first)*
              std::numeric_limits<uint16_t>::max();
          vert.push_back(tmp);
        }
        return vert;
      }

      vector<quat> GetTBNs()
      {
        vector<quat> tbns;
        quat tmp;
        vec3 bitangent;
        for(int i=0;i<m_mesh->GetNormal().size();i++)
        {
          bitangent=glm::cross(m_mesh->GetNormal()[i],m_mesh->GetTangent()[i]);
          tmp=glm::quat_cast(mat3(
                                     m_mesh->GetTangent()[i],
                                     m_mesh->GetNormal()[i],
                                     bitangent
                                     ));
          tbns.push_back(tmp);
        }
        return tbns;
      }

      vector<u8vec2> GetUVs()
      {
        vector<u8vec2> uvs;
        u8vec2 tmp;
        for(auto v:m_mesh->GetUVs())
        {
          tmp=v*std::numeric_limits<uint8_t>::max();
          uvs.push_back(tmp);
        }
        return uvs;
      }

      vector<i16vec3> GetNormals()
      {
        vector<i16vec3> normals;
        i16vec3 tmp;
        for(auto v:m_mesh->GetNormal())
        {
          tmp=v*numeric_limits<int16_t>::max();
          normals.push_back(tmp);
        }
        return normals;
      }

    private:
      Mesh* m_mesh;
      bool m_is_call_getboundsize=false;
      pair<vec3,vec3> m_bound_box;
    };
  }
}
