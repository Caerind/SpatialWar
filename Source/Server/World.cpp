#include "World.hpp"

namespace srv
{

World World::mInstance;

void World::init()
{
    terminate();

    // Load EntityManager
    mInstance.mEntities = std::shared_ptr<ses::EntityManager>(new EntityManager());

    // Load SystemManager
    mInstance.mSystems.setManager(mInstance.mEntities);
    mInstance.mSystems.addSystem<MovementSystem>();
    mInstance.mSystems.addSystem<BaseSystem>();

    // Load Game
    mInstance.mEntities->usePrefab("Planet");

    sf::Int32 playerId = mInstance.mEntities->usePrefab("Player");
    mInstance.mEntities->getComponent<BaseComponent>(playerId).setPosition(2500.f,2500.f);
}

void World::terminate()
{
    // Release EntityManager
    if (mInstance.mEntities != nullptr)
    {
        mInstance.mEntities->removeEntities();
    }

    // Release SystemManager
    mInstance.mSystems.removeSystems();
    mInstance.mSystems.setManager(nullptr);
}

void World::update(sf::Time dt)
{
    // Handle Packets
    mInstance.mEntities->handlePackets();

    // Update Entities
    mInstance.mSystems.getSystem<BaseSystem>().update();
    mInstance.mSystems.getSystem<MovementSystem>().update(dt);
}

ses::EntityManager& World::getEntities()
{
    return *mInstance.mEntities;
}

ses::SystemManager& World::getSystems()
{
    return mInstance.mSystems;
}

World::World()
: mEntities(nullptr)
, mSystems(nullptr)
{
}

World::~World()
{
    terminate();
}

} // namespace srv


