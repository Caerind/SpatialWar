#include "TransformComponent.hpp"

TransformComponent::TransformComponent()
: ses::Component()
, sf::Transformable()
{
}

std::string TransformComponent::getId()
{
    return "TransformComponent";
}

