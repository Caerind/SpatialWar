#include "EntityManager.hpp"

EntityManager::EntityManager()
: ses::EntityManager()
{
    setPrefab("Player",[&]() -> sf::Int32
    {
        sf::Int32 id = addEntity();

        // Components
        BaseComponent& b = addComponent<BaseComponent>(id);
        ShipComponent& s = addComponent<ShipComponent>(id);
        addComponent<PlayerComponent>(id);

        // Origin
        b.setOrigin(sf::Vector2f(200.f,136.f) * 0.5f);

        // Geometry
        b.setPointCount(4);
        b.setPoint(0,sf::Vector2f(0,0));
        b.setPoint(1,sf::Vector2f(200.f,0));
        b.setPoint(2,sf::Vector2f(200.f,136.f));
        b.setPoint(3,sf::Vector2f(0,136.f));

        // Base Settings
        b.setSpeed(ShipPartSystem::getMotorSpeed(0));
        b.setMass(ShipPartSystem::getMotorMass(0) + ShipPartSystem::getArmorMass(0) + ShipPartSystem::getGunMass(0));
        b.setLifeMax(ShipPartSystem::getArmor(0));
        b.restoreFullLife();

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
        BaseComponent& b = addComponent<BaseComponent>(id);
        PlanetComponent& p = addComponent<PlanetComponent>(id);

        // Geometry // Geom In First For Planet Like Component
        b.loadFromCircle(p.getShape());

        // Origin
        b.setOrigin(p.getRadius(),p.getRadius());

        // Base Settings
        b.setMass(pow(10,24)); // ~6 time smaller than the Earth
        b.setLife(10000000.f);
        return id;
    });

    setPrefab("Sun",[&]() -> sf::Int32
    {
        sf::Int32 id = addEntity();
        BaseComponent& b = addComponent<BaseComponent>(id);
        PlanetComponent& p = addComponent<PlanetComponent>(id, PlanetComponent::Type::Sun);

        // Geometry // Geom In First For Planet Like Component
        b.loadFromCircle(p.getShape());

        // Origin
        b.setOrigin(p.getRadius(),p.getRadius());

        // Base Settings
        b.setMass(2.f * pow(10,24)); // ~6 time smaller than the Earth
        b.setLife(100000000.f);

        return id;
    });

    setPrefab("Moon",[&]() -> sf::Int32
    {
        sf::Int32 id = addEntity();
        BaseComponent& b = addComponent<BaseComponent>(id);
        PlanetComponent& p = addComponent<PlanetComponent>(id, PlanetComponent::Type::Moon);

        // Geometry // Geom In First For Planet Like Component
        b.loadFromCircle(p.getShape());

        // Origin
        b.setOrigin(p.getRadius(),p.getRadius());

        // Base Settings
        b.setMass(0.75f * pow(10,24)); // ~6 time smaller than the Earth
        b.setLife(5000000.f);

        return id;
    });

    setPrefab("Comet",[&]() -> sf::Int32
    {
        sf::Int32 id = addEntity();
        BaseComponent& b = addComponent<BaseComponent>(id);
        CometComponent& c = addComponent<CometComponent>(id);

        // Origin
        b.setOrigin(sf::Vector2f(313.f,489.f) * 0.5f);

        // Geometry
        b.setPointCount(4);
        b.setPoint(0,sf::Vector2f(0,0));
        b.setPoint(1,sf::Vector2f(313.f,0));
        b.setPoint(2,sf::Vector2f(313.f,489.f));
        b.setPoint(3,sf::Vector2f(0,489.f));

        // Base Settings
        b.setMass(500.f);
        b.setLifeMax(1000.f);
        b.restoreFullLife();
        b.setSpeed(500.f);
        b.setDirection(sf::Vector2f(-0.5f,1.f));
        return id;
    });

    setPrefab("Bullet",[&]() -> sf::Int32
    {
        sf::Int32 id = addEntity();
        BaseComponent& b = addComponent<BaseComponent>(id);
        addComponent<BulletComponent>(id);
        return id;
    });

    setPrefab("Asteroid",[&]() -> sf::Int32
    {
        sf::Int32 id = addEntity();
        BaseComponent& b = addComponent<BaseComponent>(id);
        addComponent<AsteroidComponent>(id);
        return id;
    });

    setPrefab("Resource",[&]() -> sf::Int32
    {
        sf::Int32 id = addEntity();
        BaseComponent& b = addComponent<BaseComponent>(id);
        addComponent<ResourceComponent>(id);
        return id;
    });
}

void EntityManager::handlePacket(sf::Packet& packet)
{
    sf::Int32 eventId;
    packet >> eventId;

    std::cout << eventId << std::endl;

    switch (eventId)
    {
        // MovementSystem
        case 100: mSystems->handlePacket(MovementSystem::getId(),packet); break; // Move
        case 101: mSystems->handlePacket(MovementSystem::getId(),packet); break; // Position
        case 102: mSystems->handlePacket(MovementSystem::getId(),packet); break; // Rotation
        case 103: mSystems->handlePacket(MovementSystem::getId(),packet); break; // Ship Stationary

        /*
        // BaseSystem
        case 200: mSystems->handlePacket(BaseSystem::getId(),packet); break; // Set Life
        case 201: mSystems->handlePacket(BaseSystem::getId(),packet); break; // Inflige
        case 202: mSystems->handlePacket(BaseSystem::getId(),packet); break; // Restore
        case 203: mSystems->handlePacket(BaseSystem::getId(),packet); break; // Kill
        case 204: mSystems->handlePacket(BaseSystem::getId(),packet); break; // Full Restore
        case 210: mSystems->handlePacket(BaseSystem::getId(),packet); break; // Modify Mass
        case 211: mSystems->handlePacket(BaseSystem::getId(),packet); break; // Modify LifeMax
        case 212: mSystems->handlePacket(BaseSystem::getId(),packet); break; // Modify Speed
        */

        default: break;
    }
}

