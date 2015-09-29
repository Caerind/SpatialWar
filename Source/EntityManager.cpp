#include "EntityManager.hpp"

EntityManager::EntityManager()
: ses::EntityManager()
{
    setPrefab("Player",[&]() -> sf::Int32
    {
        sf::Int32 id = addEntity();
        addComponent<TransformComponent>(id);
        addComponent<ShipComponent>(id);
        addComponent<PlayerComponent>(id);
        return id;
    });
}

void EntityManager::handlePacket(sf::Packet& packet)
{
    int eventId;
    packet >> eventId;
    switch (eventId)
    {
        case 100: mSystems->handlePacket(MovementSystem::getId(),packet); break;
        case 105: mSystems->handlePacket(MovementSystem::getId(),packet); break;
        default: break;
    }
}

