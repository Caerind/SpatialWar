#include "LifeComponent.hpp"

LifeComponent::LifeComponent()
: ses::Component()
{
}

std::string LifeComponent::getId()
{
    return "LifeComponent";
}

float LifeComponent::getLife() const
{
    return mLife;
}

void LifeComponent::setLife(float life)
{
    mLife = life;
}
