#include "PlanetComponent.hpp"
#include "../World.hpp"

PlanetComponent::PlanetComponent()
: ses::Component()
{
    mSprite.setTexture(World::getResources().getTexture("planet"));
    mType = PlanetComponent::Planet;
    mRadius = 1700.f;
}

std::string PlanetComponent::getId()
{
    return "PlanetComponent";
}

PlanetComponent::Type PlanetComponent::getType() const
{
    return mType;
}

void PlanetComponent::setType(Type type)
{
    mType = type;
}

float PlanetComponent::getRadius() const
{
    return mRadius;
}

void PlanetComponent::setRadius(float radius)
{
    mRadius = radius;
}

void PlanetComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite,states);
}
