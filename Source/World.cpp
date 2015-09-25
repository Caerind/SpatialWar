#include "World.hpp"

World World::mInstance;

void World::init(bool onlineMode)
{
    terminate();
    mInstance.mOnlineMode = onlineMode;

    // Load EntityManager
    if (mInstance.mOnlineMode)
    {
        mInstance.mEntities = std::shared_ptr<ses::EntityManager>(new ClientEntityManager(Configuration::getSocket()));
    }
    else
    {
        mInstance.mEntities = std::shared_ptr<ses::EntityManager>(new EntityManager());
    }

    // Load SystemManager
    mInstance.mSystems.setManager(mInstance.mEntities);
    mInstance.mSystems.addSystem<RenderSystem>();

    // Load Resources
    //mInstance.mResources.loadTexture(...);
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

    // Release Resources
    mInstance.mResources.releaseAll();
}

void World::handleEvent(sf::Event const& event)
{
}

void World::update(sf::Time dt)
{
}

void World::render(sf::RenderTarget& target, sf::RenderStates states)
{
    mInstance.mSystems.getSystem<RenderSystem>().render(target,states);
}

bool World::isOnline()
{
    return mInstance.mOnlineMode;
}

ah::ResourceHolder& World::getResources()
{
    return mInstance.mResources;
}

World::World()
: mOnlineMode(false)
, mEntities(nullptr)
, mSystems(nullptr)
{
}

World::~World()
{
    terminate();
}


