//
// Created by moe on 2017-07-14.
//

#include "Model.hpp"

namespace Kedama
{
    StaticModel::StaticModel(const std::string& name) : GameObject(name)
    {
    }

    void StaticModel::AddMesh(StaticMesh* mesh, Material* material)
    {
        m_meshs.push_back(std::make_pair(mesh,material));
    }
}

namespace Kedama
{
    SkinningModel::SkinningModel(const std::string& name) : GameObject(name)
    {
    }

    void SkinningModel::AddMesh(SkinningMesh* mesh, Material* material)
    {
        m_meshs.push_back(std::make_pair(mesh,material));
    }
}
