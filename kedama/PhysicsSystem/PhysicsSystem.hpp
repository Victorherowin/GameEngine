//
// Created by moe on 2017-07-09.
//

#ifndef KEDAMA_PHYSICSSYSTEM_HPP
#define KEDAMA_PHYSICSSYSTEM_HPP

#include "bullet/btBulletDynamicsCommon.h"
#include "../utility/Singleton.hpp"

namespace Kedama::Physics{
    class PhysicsSystem:public Singleton<PhysicsSystem>
    {
    private:
        btDiscreteDynamicsWorld *m_dynamics_world;
    };
}
#endif //KEDAMA_PHYSICSSYSTEM_HPP
