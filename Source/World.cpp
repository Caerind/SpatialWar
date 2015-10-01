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
    mInstance.mSystems.addSystem<PlanetAttractionSystem>();
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
        mInstance.mEntities->getComponent<BaseComponent>(planetId).loadFromCircle(mInstance.mEntities->getComponent<PlanetComponent>(planetId).getShape());
        float r = mInstance.mEntities->getComponent<PlanetComponent>(planetId).getRadius();
        mInstance.mEntities->getComponent<BaseComponent>(planetId).setOrigin(r,r);
        mInstance.mEntities->getComponent<BaseComponent>(planetId).setMass(pow(10,24)); // ~6 time smaller than the Earth
        mInstance.mEntities->getComponent<BaseComponent>(planetId).setLife(1000000.f);

        sf::Int32 cometId = mInstance.mEntities->usePrefab("Comet");
        mInstance.mEntities->getComponent<BaseComponent>(cometId).setOrigin(sf::Vector2f(313.f,489.f) * 0.5f);
        mInstance.mEntities->getComponent<BaseComponent>(cometId).setPosition(sf::Vector2f(2500.f,-2500.f));
        mInstance.mEntities->getComponent<BaseComponent>(cometId).setMass(100);
        mInstance.mEntities->getComponent<BaseComponent>(cometId).setPointCount(4);
        mInstance.mEntities->getComponent<BaseComponent>(cometId).setPoint(0,sf::Vector2f(0,0));
        mInstance.mEntities->getComponent<BaseComponent>(cometId).setPoint(1,sf::Vector2f(313.f,0));
        mInstance.mEntities->getComponent<BaseComponent>(cometId).setPoint(2,sf::Vector2f(313.f,489.f));
        mInstance.mEntities->getComponent<BaseComponent>(cometId).setPoint(3,sf::Vector2f(0,489.f));
        mInstance.mEntities->getComponent<BaseComponent>(cometId).setLife(1000.f);
        mInstance.mEntities->getComponent<CometComponent>(cometId).setSpeed(400.f);
        mInstance.mEntities->getComponent<CometComponent>(cometId).setDirection(sf::Vector2f(-0.5f,1.f));

        sf::Int32 pId = mInstance.mEntities->usePrefab("Player");
        mInstance.mEntities->getComponent<BaseComponent>(pId).setOrigin(sf::Vector2f(200.f,136.f) * 0.5f);
        mInstance.mEntities->getComponent<BaseComponent>(pId).setPosition(sf::Vector2f(2500.f,2500.f));
        mInstance.mEntities->getComponent<BaseComponent>(pId).setMass(100);
        mInstance.mEntities->getComponent<BaseComponent>(pId).setPointCount(4);
        mInstance.mEntities->getComponent<BaseComponent>(pId).setPoint(0,sf::Vector2f(0,0));
        mInstance.mEntities->getComponent<BaseComponent>(pId).setPoint(1,sf::Vector2f(200.f,0));
        mInstance.mEntities->getComponent<BaseComponent>(pId).setPoint(2,sf::Vector2f(200.f,136.f));
        mInstance.mEntities->getComponent<BaseComponent>(pId).setPoint(3,sf::Vector2f(0,136.f));
        mInstance.mEntities->getComponent<BaseComponent>(pId).setLife(100.f);

        mInstance.mView.setCenter(mInstance.mEntities->getComponent<BaseComponent>(pId).getPosition());
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

    // Update Entities
    mInstance.mSystems.getSystem<BaseSystem>().update();
    mInstance.mSystems.getSystem<PlayerInputSystem>().update(dt);
    mInstance.mSystems.getSystem<PlanetAttractionSystem>().update(dt);


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


