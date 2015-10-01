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

void CometComponent::setDirection(sf::Vector2f direction)
{
    mDirection = direction;
}

sf::Vector2f CometComponent::getDirection() const
{
    return mDirection;
}

void CometComponent::setSpeed(float speed)
{
    mSpeed = speed;
}

float CometComponent::getSpeed() const
{
    return mSpeed;
}

void CometComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite,states);
}

