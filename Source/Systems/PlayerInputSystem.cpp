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
        BaseComponent& b = mEntityManager->getComponent<BaseComponent>(mEntities[i]);
        ShipComponent& s = mEntityManager->getComponent<ShipComponent>(mEntities[i]);

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

            mvt *= b.getSpeed() * dt.asSeconds();

            MovementSystem::sendMovement(mEntities[i],mvt);

            if (mvt != sf::Vector2f() && s.isStationary())
            {
                MovementSystem::sendStationary(mEntities[i],false);
            }
        }

        sf::Vector2f mPos = ah::Application::instance().getMousePositionView(World::getView());

        // Look At
        {
            sf::Vector2f d = mPos - b.getPosition();
            float rotation = 180.f - atan2(d.x,d.y) * 180.f / 3.14159265f;
            if (rotation != b.getRotation())
            {
                MovementSystem::sendRotation(mEntities[i],rotation);
            }
        }

        // Set Stationary
        if (isActive("stationary"))
        {
            MovementSystem::sendStationary(mEntities[i],!s.isStationary());
        }

        ah::Application::instance().setDebugInfo("Position",lp::to_string(b.getPosition().x) + " " + lp::to_string(b.getPosition().y));
        ah::Application::instance().setDebugInfo("Motor",lp::to_string(s.getMotorId()));
        ah::Application::instance().setDebugInfo("Armor",lp::to_string(s.getArmorId()));
        ah::Application::instance().setDebugInfo("Gun",lp::to_string(s.getGunId()));
    }

    mMap->clearEvents();
}
