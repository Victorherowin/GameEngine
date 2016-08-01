#ifndef GAMEOBJECT
#define GAMEOBJECT

#include <vector>

#include "Transform.hpp"

namespace Kedama
{
    using std::vector;
    class GameObject
    {
    public:
        GameObject(const string& name="");
        inline Transform& GetTansform(){return m_transform;}
        inline const string& GetName(){return m_name;}

        void AddNode(GameObject* node);

    private:
        void UpdateSelf();
        void UpdateChildren();

    protected:
        string m_name;
    private:
        Transform m_transform;
        GameObject* m_parent=nullptr;
        std::list<GameObject*> m_children;

        friend class Transform;
    };
}

#endif
