#include "MovementSystem.hpp"
#include "../../Lib/EntitySystem/EntityManager.hpp"
#include "../World.hpp"

MovementSystem::MovementSystem(ses::EntityManager::Ptr entityManager)
: ses::System(entityManager)
{
    mFilter.requires(TransformComponent::getId());
    std::vector<std::string> movableEntities;
    movableEntities.push_back(CometComponent::getId());
    movableEntities.push_back(BulletComponent::getId());
    movableEntities.push_back(AsteroidComponent::getId());
    movableEntities.push_back(ResourceComponent::getId());
    mFilter.requiresOne(movableEntities);
}

std::string MovementSystem::getId()
{
    return "MovementSystem";
}

void MovementSystem::update(sf::Time dt)
{
    for (std::size_t i = 0; i < mEntities.size(); i++)
    {
        if (mEntityManager->hasComponent<CometComponent>(mEntities[i]))
        {
            CometComponent& c = mEntityManager->getComponent<CometComponent>(mEntities[i]);
            sf::Vector2f u = c.getDirection();
            float l = c.getSpeed();
            sf::Vector2f mvt = u * l * dt.asSeconds();
            if (mvt != sf::Vector2f())
            {
                sf::Packet packet;
                packet << 100 << 100 << mEntities[i] << mvt;
                mEntityManager->sendPacket(packet);
            }
        }
        else if (mEntityManager->hasComponent<BulletComponent>(mEntities[i]))
        {
            BulletComponent& c = mEntityManager->getComponent<BulletComponent>(mEntities[i]);
            sf::Vector2f u = c.getDirection();
            float l = c.getSpeed();
            sf::Vector2f mvt = u * l * dt.asSeconds();
            if (mvt != sf::Vector2f())
            {
                sf::Packet packet;
                packet << 100 << 100 << mEntities[i] << mvt;
                mEntityManager->sendPacket(packet);
            }
        }
        else if (mEntityManager->hasComponent<AsteroidComponent>(mEntities[i]))
        {
            AsteroidComponent& c = mEntityManager->getComponent<AsteroidComponent>(mEntities[i]);
            sf::Vector2f u = c.getDirection();
            float l = c.getSpeed();
            c.setSpeed(l - 1.f);
            sf::Vector2f mvt = u * l * dt.asSeconds();
            if (mvt != sf::Vector2f())
            {
                sf::Packet packet;
                packet << 100 << 100 << mEntities[i] << mvt;
                mEntityManager->sendPacket(packet);
            }
        }
        else if (mEntityManager->hasComponent<ResourceComponent>(mEntities[i]))
        {
            ResourceComponent& c = mEntityManager->getComponent<ResourceComponent>(mEntities[i]);
            sf::Vector2f u = c.getDirection();
            float l = c.getSpeed();
            c.setSpeed(l - 1.f);
            sf::Vector2f mvt = u * l * dt.asSeconds();
            if (mvt != sf::Vector2f())
            {
                sf::Packet packet;
                packet << 100 << 100 << mEntities[i] << mvt;
                mEntityManager->sendPacket(packet);
            }
        }
    }
}

void MovementSystem::handlePacket(sf::Packet& packet)
{
    if (mEntityManager == nullptr)
        return;

    int eventId;
    packet >> eventId;
    switch (eventId)
    {
        case 100:
        {
            sf::Int32 entityId;
            sf::Vector2f mvt;
            packet >> entityId >> mvt;
            // Move entity
            if (mEntityManager->hasComponent<TransformComponent>(entityId))
            {
                mEntityManager->getComponent<TransformComponent>(entityId).move(mvt);
            }
            // If the entity is the player, move his view
            if (mEntityManager->hasComponent<PlayerComponent>(entityId))
            {
                mEntityManager->getComponent<PlayerComponent>(entityId).getView().move(mvt);
            }
        } break;

        case 105:
        {
            sf::Int32 entityId;
            float rotation;
            packet >> entityId >> rotation;
            if (mEntityManager->hasComponent<TransformComponent>(entityId))
            {
                mEntityManager->getComponent<TransformComponent>(entityId).setRotation(rotation);
            }
        } break;

        default: break;
    }
}
