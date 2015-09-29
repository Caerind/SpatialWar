#include "PlayerInputSystem.hpp"
#include "../../Lib/EntitySystem/EntityManager.hpp"
#include "../World.hpp"

PlayerInputSystem::PlayerInputSystem(ses::EntityManager::Ptr entityManager)
: ses::System(entityManager)
, ah::ActionTarget(Configuration::getPlayerInput())
{
    mFilter.requires(TransformComponent::getId());
    mFilter.requires(PlayerComponent::getId());
}

std::string PlayerInputSystem::getId()
{
    return "PlayerInputSystem";
}

void PlayerInputSystem::update(sf::Time dt)
{
    if (mEntityManager == nullptr)
        return;

    mMap->invokeCallbacks(mSystem,&(ah::Application::instance()));

    for (std::size_t i = 0; i < mEntities.size(); i++)
    {
        TransformComponent& t = mEntityManager->getComponent<TransformComponent>(mEntities[i]);

        // Movement
        {
            sf::Vector2f mvt;
            if (isActive("up"))
            {
                mvt.y -= 1.f;
            }
            if (isActive("left"))
            {
                mvt.x -= 1.f;
            }
            if (isActive("down"))
            {
                mvt.y += 1.f;
            }
            if (isActive("right"))
            {
                mvt.x += 1.f;
            }

            mvt *= 300.f * dt.asSeconds();

            if (mvt != sf::Vector2f())
            {
                std::cout << "PlayerInput : " << mvt.x << " " << mvt.y << std::endl;
                sf::Packet packet;
                packet << 100 << 100 << mEntities[i] << mvt;
                mEntityManager->sendPacket(packet);
            }
        }

        sf::Vector2f mPos = ah::Application::instance().getMousePositionView(World::getView());

        // Look At
        {
            sf::Vector2f d = mPos - t.getPosition();
            float rotation = 180.f - atan2(d.x,d.y) * 180.f / 3.14159265f;
            if (rotation != t.getRotation())
            {
                sf::Packet packet;
                packet << 105 << 105 << mEntities[i] << rotation;
                mEntityManager->sendPacket(packet);
            }
        }



        ah::Application::instance().setDebugInfo("Position",lp::to_string(t.getPosition().x) + " " + lp::to_string(t.getPosition().y));
    }

    mMap->clearEvents();
}

void PlayerInputSystem::handlePacket(sf::Packet& packet)
{
    int eventId;
    packet >> eventId;
    switch (eventId)
    {
        default: break;
    }
}
