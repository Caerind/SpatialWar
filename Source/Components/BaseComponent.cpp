#include "BaseComponent.hpp"

BaseComponent::BaseComponent()
: ses::Component()
, lp::CollisionShape()
{
    //ctor
}

std::string BaseComponent::getId()
{
    return "BaseComponent";
}

float BaseComponent::getLife() const
{
    return mLife;
}

void BaseComponent::setLife(float life)
{
    mLife = life;
}

void BaseComponent::inflige(float damage)
{
    mLife -= damage;
}

void BaseComponent::restore(float restore)
{
    mLife += restore;
}

bool BaseComponent::isDead() const
{
    return mLife <= 0.f;
}

float BaseComponent::getMass() const
{
    return mMass;
}

void BaseComponent::setMass(float mass)
{
    mMass = mass;
}
