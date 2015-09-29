#include "EntityManager.hpp"

EntityManager::EntityManager()
: ses::EntityManager()
{
    setPrefab("Player",[&]() -> sf::Int32
    {
        sf::Int32 id = addEntity();
        addComponent<TransformComponent>(id);
        addComponent<MassComponent>(id);
        addComponent<CollisionComponent>(id);
        addComponent<LifeComponent>(id);
        addComponent<ShipComponent>(id);
        addComponent<PlayerComponent>(id);
        return id;
    });

    setPrefab("Ship",[&]() -> sf::Int32
    {
        sf::Int32 id = addEntity();
        addComponent<TransformComponent>(id);
        addComponent<MassComponent>(id);
        addComponent<CollisionComponent>(id);
        addComponent<LifeComponent>(id);
        addComponent<ShipComponent>(id);
        return id;
    });

    setPrefab("AI",[&]() -> sf::Int32
    {
        sf::Int32 id = addEntity();
        addComponent<TransformComponent>(id);
        addComponent<MassComponent>(id);
        addComponent<CollisionComponent>(id);
        addComponent<LifeComponent>(id);
        addComponent<ShipComponent>(id);
        addComponent<AIComponent>(id);
        return id;
    });

    setPrefab("Planet",[&]() -> sf::Int32
    {
        sf::Int32 id = addEntity();
        addComponent<TransformComponent>(id);
        addComponent<MassComponent>(id);
        addComponent<CollisionComponent>(id);
        addComponent<LifeComponent>(id);
        addComponent<PlanetComponent>(id);
        return id;
    });

    setPrefab("Sun",[&]() -> sf::Int32
    {
        sf::Int32 id = addEntity();
        addComponent<TransformComponent>(id);
        addComponent<MassComponent>(id);
        addComponent<CollisionComponent>(id);
        addComponent<LifeComponent>(id);
        addComponent<PlanetComponent>(id);
        return id;
    });

    setPrefab("Moon",[&]() -> sf::Int32
    {
        sf::Int32 id = addEntity();
        addComponent<TransformComponent>(id);
        addComponent<MassComponent>(id);
        addComponent<CollisionComponent>(id);
        addComponent<LifeComponent>(id);
        addComponent<PlanetComponent>(id);
        return id;
    });

    setPrefab("Comet",[&]() -> sf::Int32
    {
        sf::Int32 id = addEntity();
        addComponent<TransformComponent>(id);
        addComponent<MassComponent>(id);
        addComponent<CollisionComponent>(id);
        addComponent<LifeComponent>(id);
        addComponent<CometComponent>(id);
        return id;
    });

    setPrefab("Bullet",[&]() -> sf::Int32
    {
        sf::Int32 id = addEntity();
        addComponent<TransformComponent>(id);
        addComponent<MassComponent>(id);
        addComponent<CollisionComponent>(id);
        addComponent<LifeComponent>(id);
        addComponent<BulletComponent>(id);
        return id;
    });

    setPrefab("Asteroid",[&]() -> sf::Int32
    {
        sf::Int32 id = addEntity();
        addComponent<TransformComponent>(id);
        addComponent<MassComponent>(id);
        addComponent<CollisionComponent>(id);
        addComponent<LifeComponent>(id);
        addComponent<AsteroidComponent>(id);
        return id;
    });

    setPrefab("Resource",[&]() -> sf::Int32
    {
        sf::Int32 id = addEntity();
        addComponent<TransformComponent>(id);
        addComponent<MassComponent>(id);
        addComponent<CollisionComponent>(id);
        addComponent<LifeComponent>(id);
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
        case 100: mSystems->handlePacket(MovementSystem::getId(),packet); break;
        case 105: mSystems->handlePacket(MovementSystem::getId(),packet); break;
        default: break;
    }
}

