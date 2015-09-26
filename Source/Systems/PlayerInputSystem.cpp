#include "PlayerInputSystem.hpp"
#include "../../Lib/EntitySystem/EntityManager.hpp"
#include "../World.hpp"

PlayerInputSystem::PlayerInputSystem(ses::EntityManager::Ptr entityManager)
: ses::System(entityManager)
, ah::ActionTarget(Configuration::getPlayerInput())
{
    mFilter.requires(TransformComponent::getId());
    mFilter.requires(SpriteComponent::getId());
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

            float speed = 300.f;

            if (isActive("speed"))
            {
                speed *= 1.5f;
            }

            mvt *= speed * dt.asSeconds();

            if (mvt != sf::Vector2f())
            {
                sf::Packet packet;
                packet << 100 << 100 << mEntities[i] << mvt;
                mEntityManager->sendPacket(packet);
            }
        }

        sf::Vector2f mPos = ah::Application::instance().getMousePositionView(World::getView());

        // Look At
        {
            sf::Vector2f d = mPos - t.getPosition();
            float rotation = 180 - atan2(d.x,d.y) * 180 / 3.14159265;
            if (rotation != t.getRotation())
            {
                sf::Packet packet;
                packet << 105 << 105 << mEntities[i] << rotation;
                mEntityManager->sendPacket(packet);
            }
        }

        World::getView().setCenter(t.getPosition());
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
