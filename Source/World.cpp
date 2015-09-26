#include "World.hpp"

World World::mInstance;

void World::init(bool onlineMode, bool server)
{
    terminate();
    mInstance.mOnlineMode = onlineMode;
    mInstance.mServer = server;

    // Load EntityManager
    if (isOnline() && !isServer())
    {
        mInstance.mEntities = std::shared_ptr<ses::EntityManager>(new ClientEntityManager(Configuration::getSocket()));
    }
    else if (!isOnline() && !isServer())
    {
        mInstance.mEntities = std::shared_ptr<ses::EntityManager>(new EntityManager());
    }
    else
    {
        mInstance.mEntities = nullptr;
    }

    // Load SystemManager
    mInstance.mSystems.setManager(mInstance.mEntities);
    mInstance.mSystems.addSystem<RenderSystem>();
    mInstance.mSystems.addSystem<PlayerInputSystem>();
    mInstance.mSystems.addSystem<MovementSystem>();

    // Load Resources
    mInstance.mResources.loadTexture("playerShip","Assets/Textures/SpaceShipNormal.png");

    // Load View
    mInstance.mView = ah::Application::instance().getDefaultView();


    // Load Game
    if (!isOnline() && !isServer())
    {
        mInstance.mEntities->usePrefab("Player");
    }
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
    mInstance.mSystems.getSystem<PlayerInputSystem>().handleEvent(event);
}

void World::update(sf::Time dt)
{
    mInstance.mSystems.getSystem<PlayerInputSystem>().update(dt);
}

void World::render(sf::RenderTarget& target, sf::RenderStates states)
{
    sf::View old = target.getView();
    target.setView(mInstance.mView);
    mInstance.mSystems.getSystem<RenderSystem>().render(target,states);
    target.setView(old);
}

bool World::isOnline()
{
    return mInstance.mOnlineMode;
}

bool World::isServer()
{
    return mInstance.mServer;
}

ah::ResourceHolder& World::getResources()
{
    return mInstance.mResources;
}

sf::View& World::getView()
{
    return mInstance.mView;
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


