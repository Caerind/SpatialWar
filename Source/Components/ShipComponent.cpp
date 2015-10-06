#include "ShipComponent.hpp"
#include "../World.hpp"

ShipComponent::ShipComponent()
: ses::Component()
, mStationary(true)
, mMotorId(0)
, mArmorId(0)
, mGunId(0)
{
    #ifdef SW_CLIENT
    mSprite.setTexture(World::getResources().getTexture("ship"));
    #endif
}

std::string ShipComponent::getId()
{
    return "ShipComponent";
}

bool ShipComponent::isStationary() const
{
    return mStationary;
}

void ShipComponent::setStationary(bool stationary)
{
    mStationary = stationary;
}

void ShipComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite,states);
}

void ShipComponent::setMotorId(int motorId)
{
    mMotorId = motorId;
}

int ShipComponent::getMotorId() const
{
    return mMotorId;
}

void ShipComponent::setArmorId(int armorId)
{
    mArmorId = armorId;
}

int ShipComponent::getArmorId() const
{
    return mArmorId;
}

void ShipComponent::setGunId(int gunId)
{
    mGunId = gunId;
}

int ShipComponent::getGunId() const
{
    return mGunId;
}
