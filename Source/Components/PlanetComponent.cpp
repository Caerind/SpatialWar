#include "PlanetComponent.hpp"
#include "../World.hpp"

PlanetComponent::PlanetComponent()
: ses::Component()
{
    sf::Texture* texture = &World::getResources().getTexture("planet");
    mShape.setRadius(texture->getSize().x * 0.5f);
    mShape.setTexture(texture);
    mType = PlanetComponent::Planet;
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
    return mShape.getRadius();
}

void PlanetComponent::setRadius(float radius)
{
    mShape.setRadius(radius);
}

void PlanetComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mShape,states);
}

sf::CircleShape& PlanetComponent::getShape()
{
    return mShape;
}
