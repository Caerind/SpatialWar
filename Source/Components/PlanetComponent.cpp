#include "PlanetComponent.hpp"
#include "../World.hpp"

PlanetComponent::PlanetComponent(PlanetComponent::Type type)
: ses::Component()
, mType(type)
{
    sf::Texture* texture = nullptr;
    if (mType == PlanetComponent::Type::Planet)
    {
        texture = &World::getResources().getTexture("planet");
    }
    else if (mType == PlanetComponent::Type::Sun)
    {
        texture = &World::getResources().getTexture("planet");
    }
    else // Moon
    {
        texture = &World::getResources().getTexture("planet");
    }

    if (texture != nullptr)
    {
        mShape.setRadius(texture->getSize().x * 0.5f);
        mShape.setTexture(texture);
    }
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
