#include "CometComponent.hpp"
#include "../World.hpp"

CometComponent::CometComponent()
: ses::Component()
{
    mSprite.setTexture(World::getResources().getTexture("comet"));
}

std::string CometComponent::getId()
{
    return "CometComponent";
}

void CometComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite,states);
}

