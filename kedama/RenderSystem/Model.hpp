//
// Created by moe on 2017-07-14.
//

#ifndef KEDAMA_MODEL_HPP
#define KEDAMA_MODEL_HPP

#include "../Include.hpp"
#include "../Define.hpp"
#include "Mesh.hpp"
#include "../GameObject/GameObject.hpp"

namespace Kedama
{
    using namespace std;
    class KEDAMA_API StaticModel:public GameObject
    {
    public:
        StaticModel(const string& name="StaticModel");
        void AddMesh(StaticMesh* mesh,Material* material= nullptr);
    private:

        vector<pair<StaticMesh*,Material*>> m_meshs;
    };

    class KEDAMA_API SkinningModel:public GameObject
    {
    public:
        SkinningModel(const string& name="SkinnedModel");
        void AddMesh(SkinningMesh* mesh,Material* material= nullptr);
    private:

        vector<pair<SkinningMesh*,Material*>> m_meshs;
    };
}

#endif //KEDAMA_MODEL_HPP
