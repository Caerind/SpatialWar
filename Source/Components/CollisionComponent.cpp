#include "CollisionComponent.hpp"

CollisionComponent::CollisionComponent()
: ses::Component()
{
}

std::string CollisionComponent::getId()
{
    return "CollisionComponent";
}
