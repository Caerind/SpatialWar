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

void AsteroidComponent::setDirection(sf::Vector2f direction)
{
    mDirection = direction;
}

sf::Vector2f AsteroidComponent::getDirection() const
{
    return mDirection;
}

void AsteroidComponent::setSpeed(float speed)
{
    mSpeed = speed;
}

float AsteroidComponent::getSpeed() const
{
    return mSpeed;
}

void AsteroidComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite,states);
}
