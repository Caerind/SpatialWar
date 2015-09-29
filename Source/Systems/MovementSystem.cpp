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
            // Move entity
            if (mEntityManager->hasComponent<TransformComponent>(entityId))
            {
                mEntityManager->getComponent<TransformComponent>(entityId).move(mvt);
            }
            // If the entity is the player, move his view
            if (mEntityManager->hasComponent<PlayerComponent>(entityId))
            {
                mEntityManager->getComponent<PlayerComponent>(entityId).getView().move(mvt);
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
            }
        } break;

        default: break;
    }
}
