#include "AsteroidComponent.hpp"
#include "../World.hpp"

AsteroidComponent::AsteroidComponent()
: ses::Component()
{
    // TODO : mSprite.setTexture(World::getResources().getTexture("asteroid"));
}

std::string AsteroidComponent::getId()
{
    return "AsteroidComponent";
}

void AsteroidComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite,states);
}
