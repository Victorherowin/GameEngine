#ifndef GAMEOBJECT
#define GAMEOBJECT

#include <vector>

#include "Transform.hpp"
#include "Config.hpp"

namespace Kedama
{
  DEFINE_RAW_PTR(GameObject)

  using std::vector;

  class GameObject
  {
  public:
    GameObject(const string& name="");
    virtual ~GameObject();
    inline Transform& GetTansform(){return m_transform;}
    inline const string& GetName(){return m_name;}

    void AddNode(GameObjectPtr node);

  private:
    void UpdateSelf();
    void UpdateChildren();

  protected:
    string m_name;
  private:
    Transform m_transform;
    GameObjectPtr m_parent=nullptr;
    std::list<GameObjectPtr> m_children;

    friend class Transform;
  };
}

#endif
