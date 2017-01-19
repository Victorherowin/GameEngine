#ifndef BATCH
#define BATCH

#include "Mesh.hpp"

#include "../Include.hpp"
#include "../GameObject/GameObject.hpp"

namespace Kedama {

  class Batch
  {
  public:

    inline void AddInstance(BaseModel* obj)
    {m_instancies.push_back(obj);}

    inline list<BaseModel*>& GetInstancies()
    {return m_instancies;}

  private:
    list<BaseModel*> m_instancies;
  };

}
#endif
