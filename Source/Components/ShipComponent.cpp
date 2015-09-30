#include "ShipComponent.hpp"
#include "../World.hpp"

ShipComponent::ShipComponent()
: ses::Component()
{
    mSprite.setTexture(World::getResources().getTexture("ship"));
}

std::string ShipComponent::getId()
{
    return "ShipComponent";
}

bool ShipComponent::isStationary() const
{
    return mStationary;
}

void ShipComponent::setStationary(bool stationary)
{
    mStationary = stationary;
}

void ShipComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite,states);
}
