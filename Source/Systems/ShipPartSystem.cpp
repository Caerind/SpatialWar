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

void ShipPartSystem::changeMotor(sf::Int32 const& entityId, int motorId)
{
    if (std::find(mEntities.begin(), mEntities.end(), entityId) != mEntities.end())
    {
        ShipComponent& s = mEntityManager->getComponent<ShipComponent>(entityId);

        // Old Motor
        int oldMotor = s.getMotorId();
        {
            sf::Packet packet;
            sf::Int32 msgId = 210;
            packet << msgId << msgId << entityId << -1.f * getMotorMass(oldMotor);
            mEntityManager->sendPacket(packet);
        }
        {
            sf::Packet packet;
            sf::Int32 msgId = 212;
            packet << msgId << msgId << entityId << -1.f * getMotorSpeed(oldMotor);
            mEntityManager->sendPacket(packet);
        }

        // New Motor
        s.setMotorId(motorId);
        {
            sf::Packet packet;
            sf::Int32 msgId = 210;
            packet << msgId << msgId << entityId << 1.f * getMotorMass(motorId);
            mEntityManager->sendPacket(packet);
        }
        {
            sf::Packet packet;
            sf::Int32 msgId = 212;
            packet << msgId << msgId << entityId << 1.f * getMotorSpeed(motorId);
            mEntityManager->sendPacket(packet);
        }
    }
}

void ShipPartSystem::changeArmor(sf::Int32 const& entityId, int armorId)
{
    if (std::find(mEntities.begin(), mEntities.end(), entityId) != mEntities.end())
    {
        ShipComponent& s = mEntityManager->getComponent<ShipComponent>(entityId);

        // Old Armor
        int oldArmor = s.getArmorId();
        {
            sf::Packet packet;
            sf::Int32 msgId = 210;
            packet << msgId << msgId << entityId << -1.f * getArmorMass(oldArmor);
            mEntityManager->sendPacket(packet);
        }
        {
            sf::Packet packet;
            sf::Int32 msgId = 211;
            packet << msgId << msgId << entityId << -1.f * getArmor(oldArmor);
            mEntityManager->sendPacket(packet);
        }

        // New Armor
        s.setArmorId(armorId);
        {
            sf::Packet packet;
            sf::Int32 msgId = 210;
            packet << msgId << msgId << entityId << 1.f * getArmorMass(armorId);
            mEntityManager->sendPacket(packet);
        }
        {
            sf::Packet packet;
            sf::Int32 msgId = 211;
            packet << msgId << msgId << entityId << 1.f * getArmor(armorId);
            mEntityManager->sendPacket(packet);
        }

    }
}

void ShipPartSystem::changeGun(sf::Int32 const& entityId, int gunId)
{
    if (std::find(mEntities.begin(), mEntities.end(), entityId) != mEntities.end())
    {
        ShipComponent& s = mEntityManager->getComponent<ShipComponent>(entityId);

        // Old Gun
        int oldGun = s.getGunId();
        {
            sf::Packet packet;
            sf::Int32 msgId = 210;
            packet << msgId << msgId << entityId << -1.f * getGunMass(oldGun);
            mEntityManager->sendPacket(packet);
        }

        // New Gun
        s.setGunId(gunId);
        {
            sf::Packet packet;
            sf::Int32 msgId = 210;
            packet << msgId << msgId << entityId << 1.f * getGunMass(gunId);
            mEntityManager->sendPacket(packet);
        }
    }
}

float ShipPartSystem::getMotorSpeed(int motorId)
{
    float value;
    switch (motorId)
    {
        case 0: value = 300.f; break;
        case 1: value = 400.f; break;
        case 2: value = 500.f; break;

        default: value = 300.f; break; // Equal to case 0
    }
    return value;
}

float ShipPartSystem::getMotorMass(int motorId)
{
    float value;
    switch (motorId)
    {
        case 0: value = 100.f; break;
        case 1: value = 200.f; break;
        case 2: value = 300.f; break;

        default: value = 100.f; break; // Equal to case 0
    }
    return value;
}

float ShipPartSystem::getArmor(int armorId)
{
    float value;
    switch (armorId)
    {
        case 0: value = 200.f; break;
        case 1: value = 250.f; break;
        case 2: value = 300.f; break;

        default: value = 200.f; break; // Equal to case 0
    }
    return value;
}

float ShipPartSystem::getArmorMass(int armorId)
{
    float value;
    switch (armorId)
    {
        case 0: value = 100.f; break;
        case 1: value = 200.f; break;
        case 2: value = 300.f; break;

        default: value = 100.f; break; // Equal to case 0
    }
    return value;
}

float ShipPartSystem::getGunStrength(int gunId)
{
    float value;
    switch (gunId)
    {
        case 0: value = 50.f; break;
        case 1: value = 75.f; break;
        case 2: value = 100.f; break;

        default: value = 50.f; break; // Equal to case 0
    }
    return value;
}

float ShipPartSystem::getGunMass(int gunId)
{
    float value;
    switch (gunId)
    {
        case 0: value = 100.f; break;
        case 1: value = 200.f; break;
        case 2: value = 300.f; break;

        default: value = 100.f; break; // Equal to case 0
    }
    return value;
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
