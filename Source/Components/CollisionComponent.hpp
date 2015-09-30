#ifndef COLLISIONCOMPONENT_HPP
#define COLLISIONCOMPONENT_HPP

#include "../../Lib/EntitySystem/Component.hpp"
#include "../../Lib/Aharos/Helper/CollisionShape.hpp"

class CollisionComponent : public ses::Component
{
    public:
        CollisionComponent();

        static std::string getId();

        lp::CollisionShape& getShape();

    private:
        lp::CollisionShape::Ptr mShape;
};

#endif // COLLISIONCOMPONENT_HPP
