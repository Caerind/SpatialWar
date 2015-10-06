#include "BulletComponent.hpp"
#include "../World.hpp"

BulletComponent::BulletComponent()
: ses::Component()
{
    #ifdef SW_CLIENT
    // TODO : mSprite.setTexture(World::getResources().getTexture("bullet"));
    #endif
}

std::string BulletComponent::getId()
{
    return "BulletComponent";
}

void BulletComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite,states);
}
