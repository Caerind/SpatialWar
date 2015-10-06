#include "World.hpp"

World World::mInstance;

void World::init()
{
    terminate();

    // Load EntityManager & SystemManager
    mInstance.mEntities = std::shared_ptr<ses::EntityManager>(new EntityManager());
    mInstance.mSystems.setManager(mInstance.mEntities);
    if (isClient())
    {
        mInstance.mSystems.addSystem<RenderSystem>();
        mInstance.mSystems.addSystem<PlayerInputSystem>();
    }
    else
    {
        //mInstance.mSystems.addSystem<RenderSystem>(); // TODO : If we want to render the world latter in server
        mInstance.mSystems.addSystem<MovementSystem>();
        mInstance.mSystems.addSystem<BaseSystem>();
    }


    // Load Resources
    mInstance.mResources.loadTexture("ship","Assets/Textures/SpaceShipNormal.png");
    mInstance.mResources.loadTexture("spaceBackground","Assets/Textures/spaceBackground.png");
    mInstance.mResources.loadTexture("planet","Assets/Textures/planet.png");
    mInstance.mResources.loadTexture("comet","Assets/Textures/comet.png");
    mInstance.mResources.loadTexture("asteroids","Assets/Textures/asteroids.png");

    // Load View
    mInstance.mView = ah::Application::instance().getDefaultView();
    mInstance.mView.zoom(8.f);

    if (isServer())
    {
        // Load Game
        mInstance.mEntities->usePrefab("Planet");
    }


    // Init Socket
    #ifdef SW_CLIENT

    mInstance.mSocket.setBlocking(true);
    while (mInstance.mSocket.connect(Configuration::getServerAddress(),Configuration::getServerPort()) != sf::Socket::Done)
    {
        sf::sleep(sf::seconds(0.001f));
    }
    mInstance.mSocket.setBlocking(false);

    #endif // SW_CLIENT
}

void World::terminate()
{
    // Deconnect Socket
    #ifdef SW_CLIENT


    #endif // SW_CLIENT

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

    if (mInstance.mSystems.hasSystem<PlayerInputSystem>()) // TODO : Optimize with #ifdef
    {
        mInstance.mSystems.getSystem<PlayerInputSystem>().handleEvent(event);
    }
}

void World::update(sf::Time dt)
{
    // Handle Packets
    mInstance.mEntities->handlePackets();

    // Update Entities
    if (mInstance.mSystems.hasSystem<BaseSystem>())
    {
        mInstance.mSystems.getSystem<BaseSystem>().update();
    }
    if (mInstance.mSystems.hasSystem<MovementSystem>())
    {
        mInstance.mSystems.getSystem<MovementSystem>().update(dt);
    }
    if (mInstance.mSystems.hasSystem<PlayerInputSystem>())
    {
        mInstance.mSystems.getSystem<PlayerInputSystem>().update(dt);
    }

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
    if (mInstance.mSystems.hasSystem<RenderSystem>())
    {
        mInstance.mSystems.getSystem<RenderSystem>().render(target,states);
    }

    target.setView(old);
}

bool World::isClient()
{
    #ifdef SW_CLIENT
    return true;
    #endif
    return false;
}

bool World::isServer()
{
    #ifdef SW_SERVER
    return true;
    #endif
    return false;
}

#ifdef SW_CLIENT
sf::TcpSocket& World::getSocket()
{
    return mInstance.mSocket;
}
#endif

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
: mEntities(nullptr)
, mSystems(nullptr)
{
}

World::~World()
{
    terminate();
}


