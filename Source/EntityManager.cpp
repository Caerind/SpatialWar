#include "EntityManager.hpp"

EntityManager::EntityManager()
: ses::EntityManager()
{
    setPrefab("Player",[&]() -> sf::Int32
    {
        sf::Int32 id = addEntity();
        TransformComponent& t = addComponent<TransformComponent>(id);
        SpriteComponent& s = addComponent<SpriteComponent>(id,"playerShip");
        t.setOrigin(s.getGlobalBounds().width/2,s.getGlobalBounds().height/2);
        t.setPosition(400,300);
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

