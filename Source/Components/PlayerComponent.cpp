#include "PlayerComponent.hpp"
#include "../World.hpp"

PlayerComponent::PlayerComponent()
: ses::Component()
, mView(World::getView())
{
}

std::string PlayerComponent::getId()
{
    return "PlayerComponent";
}

sf::View& PlayerComponent::getView()
{
    return mView;
}
