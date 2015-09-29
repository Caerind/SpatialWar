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

void ShipComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite,states);
}
