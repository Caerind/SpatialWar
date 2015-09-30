#include "PlayerInputSystem.hpp"
#include "../../Lib/EntitySystem/EntityManager.hpp"
#include "../World.hpp"

PlayerInputSystem::PlayerInputSystem(ses::EntityManager::Ptr entityManager)
: ses::System(entityManager)
, ah::ActionTarget(Configuration::getPlayerInput())
{
    mFilter.requires(BaseComponent::getId());
    mFilter.requires(PlayerComponent::getId());
    mFilter.requires(ShipComponent::getId());
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
        BaseComponent& t = mEntityManager->getComponent<BaseComponent>(mEntities[i]);

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
                sf::Packet packet;
                packet << 100 << 100 << mEntities[i] << mvt;
                mEntityManager->sendPacket(packet);

                if (mEntityManager->getComponent<ShipComponent>(mEntities[i]).isStationary())
                {
                    mEntityManager->getComponent<ShipComponent>(mEntities[i]).setStationary(false);
                }
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

        // Set Stationary
        if (isActive("stationary"))
        {
            mEntityManager->getComponent<ShipComponent>(mEntities[i]).setStationary(true);
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
