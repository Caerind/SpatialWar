#include "MassComponent.hpp"

MassComponent::MassComponent()
: ses::Component()
{
}

std::string MassComponent::getId()
{
    return "MassComponent";
}

float MassComponent::getMass() const
{
    return mMass;
}

void MassComponent::setMass(float mass)
{
    mMass = mass;
}
