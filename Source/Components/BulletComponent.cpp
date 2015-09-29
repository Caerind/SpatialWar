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

void BulletComponent::setDirection(sf::Vector2f direction)
{
    mDirection = direction;
}

sf::Vector2f BulletComponent::getDirection() const
{
    return mDirection;
}

void BulletComponent::setSpeed(float speed)
{
    mSpeed = speed;
}

float BulletComponent::getSpeed() const
{
    return mSpeed;
}

void BulletComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite,states);
}
