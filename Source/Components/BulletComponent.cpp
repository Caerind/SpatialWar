#include "BulletComponent.hpp"
#include "../World.hpp"

BulletComponent::BulletComponent()
: ses::Component()
{
    // TODO : mSprite.setTexture(World::getResources().getTexture("bullet"));
}

std::string BulletComponent::getId()
{
    return "BulletComponent";
}

void BulletComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite,states);
}
