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
    mInstance.mResources.loadTexture("ship","Assets/Textures/SpaceShipNormal.png");
    mInstance.mResources.loadTexture("spaceBackground","Assets/Textures/spaceBackground.png");

    // Load View
    mInstance.mView = ah::Application::instance().getDefaultView();

    // Load Game
    if (!isOnline() && !isServer())
    {
        sf::Int32 pId = mInstance.mEntities->usePrefab("Player");
        mInstance.mEntities->getComponent<TransformComponent>().setOrigin(sf::Vector2f(200.f,136.f) * 0.5f);
        mInstance.mEntities->getComponent<TransformComponent>().setPosition(sf::Vector2f(400.f,300.f));
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

    // Release Space
    mInstance.mSpace.clear();

    // Release Resources
    mInstance.mResources.releaseAll();
}

void World::handleEvent(sf::Event const& event)
{
    if (event.type == sf::Event::MouseWheelScrolled && event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
    {
        if (event.mouseWheelScroll.delta < 1)
        {
            if (mInstance.mView.getSize().x < 8000.f)
            {
                mInstance.mView.zoom(1.2f);
            }
        }
        else if (event.mouseWheelScroll.delta)
        {
            if (mInstance.mView.getSize().x > 500.f)
            {
                mInstance.mView.zoom(0.8f);
            }
        }
    }
    mInstance.mSystems.getSystem<PlayerInputSystem>().handleEvent(event);
}

void World::update(sf::Time dt)
{
    // Handle Packets
    mInstance.mEntities->handlePackets();

    // Update Entities
    mInstance.mSystems.getSystem<PlayerInputSystem>().update(dt);


    // Background
    mInstance.mSpace.update(mInstance.mView);
}

void World::render(sf::RenderTarget& target, sf::RenderStates states)
{
    sf::View old = target.getView();
    target.setView(mInstance.mView);

    // Background
    target.draw(mInstance.mSpace,states);

    // Entities
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

Space& World::getSpace()
{
    return mInstance.mSpace;
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


