#include "EntityManager.hpp"

EntityManager::EntityManager()
: ses::EntityManager()
{
    setPrefab("Player",[&]() -> sf::Int32
    {
        sf::Int32 id = addEntity();
        BaseComponent& b = addComponent<BaseComponent>(id);
        ShipComponent& s = addComponent<ShipComponent>(id);
        b.setSpeed(ShipPartSystem::getMotorSpeed(0));
        b.setMass(ShipPartSystem::getMotorMass(0) + ShipPartSystem::getArmorMass(0) + ShipPartSystem::getGunMass(0));
        b.setLifeMax(ShipPartSystem::getArmor(0));
        b.restoreFullLife();
        addComponent<PlayerComponent>(id);
        return id;
    });

    setPrefab("Ship",[&]() -> sf::Int32
    {
        sf::Int32 id = addEntity();
        BaseComponent& b = addComponent<BaseComponent>(id);
        ShipComponent& s = addComponent<ShipComponent>(id);
        b.setSpeed(ShipPartSystem::getMotorSpeed(0));
        b.setMass(ShipPartSystem::getMotorMass(0) + ShipPartSystem::getArmorMass(0) + ShipPartSystem::getGunMass(0));
        b.setLifeMax(ShipPartSystem::getArmor(0));
        b.restoreFullLife();
        return id;
    });

    setPrefab("AI",[&]() -> sf::Int32
    {
        sf::Int32 id = addEntity();
        BaseComponent& b = addComponent<BaseComponent>(id);
        ShipComponent& s = addComponent<ShipComponent>(id);
        b.setSpeed(ShipPartSystem::getMotorSpeed(0));
        b.setMass(ShipPartSystem::getMotorMass(0) + ShipPartSystem::getArmorMass(0) + ShipPartSystem::getGunMass(0));
        b.setLifeMax(ShipPartSystem::getArmor(0));
        b.restoreFullLife();
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
    sf::Int32 eventId;
    packet >> eventId;

    std::cout << static_cast<sf::Int32>(eventId) << std::endl;

    switch (eventId)
    {
        // MovementSystem
        case 100: mSystems->handlePacket(MovementSystem::getId(),packet); break; // Move
        case 105: mSystems->handlePacket(MovementSystem::getId(),packet); break; // Rotate
        case 110: mSystems->handlePacket(MovementSystem::getId(),packet); break; // Ship Stationary

        // BaseSystem
        case 200: mSystems->handlePacket(BaseSystem::getId(),packet); break; // Set Life
        case 201: mSystems->handlePacket(BaseSystem::getId(),packet); break; // Inflige
        case 202: mSystems->handlePacket(BaseSystem::getId(),packet); break; // Restore
        case 203: mSystems->handlePacket(BaseSystem::getId(),packet); break; // Kill
        case 204: mSystems->handlePacket(BaseSystem::getId(),packet); break; // Full Restore
        case 210: mSystems->handlePacket(BaseSystem::getId(),packet); break; // Modify Mass
        case 211: mSystems->handlePacket(BaseSystem::getId(),packet); break; // Modify LifeMax
        case 212: mSystems->handlePacket(BaseSystem::getId(),packet); break; // Modify Speed

        default: break;
    }
}

