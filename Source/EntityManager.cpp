#include "EntityManager.hpp"

EntityManager::EntityManager()
: ses::EntityManager()
{
    setPrefab("Player",[&]() -> sf::Int32
    {
        sf::Int32 id = addEntity();
        addComponent<BaseComponent>(id);
        addComponent<ShipComponent>(id);
        addComponent<PlayerComponent>(id);
        return id;
    });

    setPrefab("Ship",[&]() -> sf::Int32
    {
        sf::Int32 id = addEntity();
        addComponent<BaseComponent>(id);
        addComponent<ShipComponent>(id);
        return id;
    });

    setPrefab("AI",[&]() -> sf::Int32
    {
        sf::Int32 id = addEntity();
        addComponent<BaseComponent>(id);
        addComponent<ShipComponent>(id);
        addComponent<AIComponent>(id);
        return id;
    });

    setPrefab("Planet",[&]() -> sf::Int32
    {
        sf::Int32 id = addEntity();
        addComponent<BaseComponent>(id);
        addComponent<PlanetComponent>(id);
        return id;
    });

    setPrefab("Sun",[&]() -> sf::Int32
    {
        sf::Int32 id = addEntity();
        addComponent<BaseComponent>(id);
        addComponent<PlanetComponent>(id);
        return id;
    });

    setPrefab("Moon",[&]() -> sf::Int32
    {
        sf::Int32 id = addEntity();
        addComponent<BaseComponent>(id);
        addComponent<PlanetComponent>(id);
        return id;
    });

    setPrefab("Comet",[&]() -> sf::Int32
    {
        sf::Int32 id = addEntity();
        addComponent<BaseComponent>(id);
        addComponent<CometComponent>(id);
        return id;
    });

    setPrefab("Bullet",[&]() -> sf::Int32
    {
        sf::Int32 id = addEntity();
        addComponent<BaseComponent>(id);
        addComponent<BulletComponent>(id);
        return id;
    });

    setPrefab("Asteroid",[&]() -> sf::Int32
    {
        sf::Int32 id = addEntity();
        addComponent<BaseComponent>(id);
        addComponent<AsteroidComponent>(id);
        return id;
    });

    setPrefab("Resource",[&]() -> sf::Int32
    {
        sf::Int32 id = addEntity();
        addComponent<BaseComponent>(id);
        addComponent<ResourceComponent>(id);
        return id;
    });
}

void EntityManager::handlePacket(sf::Packet& packet)
{
    int eventId;
    packet >> eventId;
    switch (eventId)
    {
        // MovementSystem
        case 100: mSystems->handlePacket(MovementSystem::getId(),packet); break;
        case 105: mSystems->handlePacket(MovementSystem::getId(),packet); break;

        // BaseSystem
        case 200: mSystems->handlePacket(BaseSystem::getId(),packet); break;
        case 201: mSystems->handlePacket(BaseSystem::getId(),packet); break;
        case 202: mSystems->handlePacket(BaseSystem::getId(),packet); break;
        case 203: mSystems->handlePacket(BaseSystem::getId(),packet); break;

        default: break;
    }
}

