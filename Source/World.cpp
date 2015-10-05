#include "World.hpp"

World World::mInstance;

void World::init(bool onlineMode, bool server)
{
    terminate();
    mInstance.mOnlineMode = onlineMode;
    mInstance.mServer = server;

    // Load EntityManager
    mInstance.mEntities = std::shared_ptr<ses::EntityManager>(new EntityManager());

    // Load SystemManager
    mInstance.mSystems.setManager(mInstance.mEntities);
    mInstance.mSystems.addSystem<RenderSystem>();
    mInstance.mSystems.addSystem<PlayerInputSystem>();
    mInstance.mSystems.addSystem<MovementSystem>();
    mInstance.mSystems.addSystem<BaseSystem>();

    // Load Resources
    mInstance.mResources.loadTexture("ship","Assets/Textures/SpaceShipNormal.png");
    mInstance.mResources.loadTexture("spaceBackground","Assets/Textures/spaceBackground.png");
    mInstance.mResources.loadTexture("planet","Assets/Textures/planet.png");
    mInstance.mResources.loadTexture("comet","Assets/Textures/comet.png");
    mInstance.mResources.loadTexture("asteroids","Assets/Textures/asteroids.png");

    // Load View
    mInstance.mView = ah::Application::instance().getDefaultView();
    mInstance.mView.zoom(8.f);

    // Load Game
    if (!isOnline() && !isServer())
    {
        sf::Int32 planetId = mInstance.mEntities->usePrefab("Planet");

        sf::Int32 playerId = mInstance.mEntities->usePrefab("Player");
        mInstance.mEntities->getComponent<BaseComponent>(playerId).setPosition(2500.f,2500.f);

        mInstance.mView.setCenter(mInstance.mEntities->getComponent<BaseComponent>(playerId).getPosition());
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
        else
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

    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        // Update Entities
        mInstance.mSystems.getSystem<BaseSystem>().update();
        mInstance.mSystems.getSystem<MovementSystem>().update(dt);
        mInstance.mSystems.getSystem<PlayerInputSystem>().update(dt);


        // Background
        mInstance.mSpace.update(mInstance.mView);
    }

    ah::Application::instance().setDebugInfo("Entities",lp::to_string(mInstance.mEntities->entitiesCount()));
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

ses::EntityManager& World::getEntities()
{
    return *mInstance.mEntities;
}

ses::SystemManager& World::getSystems()
{
    return mInstance.mSystems;
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


