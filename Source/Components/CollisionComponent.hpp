#ifndef COLLISIONCOMPONENT_HPP
#define COLLISIONCOMPONENT_HPP

#include "../../Lib/EntitySystem/Component.hpp"

class CollisionComponent : public ses::Component
{
    public:
        CollisionComponent();

        static std::string getId();
};

#endif // COLLISIONCOMPONENT_HPP
