#include "ShipPartSystem.hpp"
#include "../../Lib/EntitySystem/EntityManager.hpp"

ShipPartSystem::ShipPartSystem(ses::EntityManager::Ptr entityManager)
: ses::System(entityManager)
{
    mFilter.requires(ShipComponent::getId());
}

std::string ShipPartSystem::getId()
{
    return "ShipPartSystem";
}



void ShipPartSystem::update()
{
}

void ShipPartSystem::changeMotor(sf::Int32 const& entityId, int motorId)
{
    if (std::find(mEntities.begin(), mEntities.end(), entityId) != mEntities.end())
    {
        ShipComponent& s = mEntityManager->getComponent<ShipComponent>(entityId);

        // REMOVE LAST MOTOR
        int oldMotor = s.getMotorId();


        // SET THE NEW
        s.setMotorId(motorId);

    }
}

void ShipPartSystem::changeArmor(sf::Int32 const& entityId, int armorId)
{
    if (std::find(mEntities.begin(), mEntities.end(), entityId) != mEntities.end())
    {
        ShipComponent& s = mEntityManager->getComponent<ShipComponent>(entityId);

        // REMOVE LAST MOTOR
        int oldArmor = s.getArmorId();


        // SET THE NEW
        s.setArmorId(armorId);

    }
}

void ShipPartSystem::changeGun(sf::Int32 const& entityId, int gunId)
{
    if (std::find(mEntities.begin(), mEntities.end(), entityId) != mEntities.end())
    {
        ShipComponent& s = mEntityManager->getComponent<ShipComponent>(entityId);

        // REMOVE LAST MOTOR
        int oldGun = s.getGunId();


        // SET THE NEW
        s.setGunId(gunId);

    }
}

void ShipPartSystem::handlePacket(sf::Packet& packet)
{
    sf::Int32 eventId;
    packet >> eventId;
    switch (eventId)
    {
        default: break;
    }
}
