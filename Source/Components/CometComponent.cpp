#include "CometComponent.hpp"
#include "../World.hpp"

CometComponent::CometComponent()
: ses::Component()
{
    #ifdef SW_CLIENT
    mSprite.setTexture(World::getResources().getTexture("comet"));
    #endif
}

std::string CometComponent::getId()
{
    return "CometComponent";
}

void CometComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite,states);
}

