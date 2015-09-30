#include "CollisionComponent.hpp"

CollisionComponent::CollisionComponent()
: ses::Component()
, mShape(std::shared_ptr<lp::CollisionShape>())
{
}

std::string CollisionComponent::getId()
{
    return "CollisionComponent";
}

lp::CollisionShape& CollisionComponent::getShape()
{
    return *mShape;
}
