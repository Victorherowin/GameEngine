#ifndef BATCH
#define BATCH

#include "Mesh.hpp"

#include "../Include.hpp"
#include "../GameObject/GameObject.hpp"

namespace Kedama {

  class Batch
  {
  public:

    inline void AddInstance(BaseModelPtr& obj)
    {m_instancies.push_back(obj);}

    inline list<BaseModelPtr>& GetInstancies()
    {return m_instancies;}

  private:
    list<BaseModelPtr> m_instancies;
  };

}
#endif
