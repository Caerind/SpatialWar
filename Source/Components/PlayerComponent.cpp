#include "PlayerComponent.hpp"

PlayerComponent::PlayerComponent()
: ses::Component()
{
}

std::string PlayerComponent::getId()
{
    return "PlayerComponent";
}
