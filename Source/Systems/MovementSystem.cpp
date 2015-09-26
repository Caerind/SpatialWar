#include "MovementSystem.hpp"
#include "../../Lib/EntitySystem/EntityManager.hpp"
#include "../World.hpp"

MovementSystem::MovementSystem(ses::EntityManager::Ptr entityManager)
: ses::System(entityManager)
{
}

std::string MovementSystem::getId()
{
    return "MovementSystem";
}

void MovementSystem::handlePacket(sf::Packet& packet)
{
    if (mEntityManager == nullptr)
        return;

    int eventId;
    packet >> eventId;
    switch (eventId)
    {
        case 100:
        {
            sf::Int32 entityId;
            sf::Vector2f mvt;
            packet >> entityId >> mvt;
            if (mEntityManager->hasComponent<TransformComponent>(entityId))
            {
                mEntityManager->getComponent<TransformComponent>(entityId).move(mvt);
                /*
                if (World::isServer())
                {
                    sf::Packet packet;
                    packet << 100 << 100 << 100 << entityId << mvt;
                    mEntityManager->sendPacket(packet);
                }
                */
            }
        } break;

        case 105:
        {
            sf::Int32 entityId;
            float rotation;
            packet >> entityId >> rotation;
            if (mEntityManager->hasComponent<TransformComponent>(entityId))
            {
                mEntityManager->getComponent<TransformComponent>(entityId).setRotation(rotation);
                /*
                if (World::isServer())
                {
                    sf::Packet packet;
                    packet << 105 << 105 << 105 << entityId << rotation;
                    mEntityManager->sendPacket(packet);
                }
                */
            }
        } break;

        default: break;
    }
}
