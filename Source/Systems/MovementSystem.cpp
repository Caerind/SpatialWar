#include "MovementSystem.hpp"
#include "../../Lib/EntitySystem/EntityManager.hpp"
#include "../World.hpp"

MovementSystem::MovementSystem(ses::EntityManager::Ptr entityManager)
: ses::System(entityManager)
{
    mFilter.requires(BaseComponent::getId());
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
                sf::Int32 msgId = 100;
                packet << msgId << msgId << mEntities[i] << mvt;
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
                sf::Int32 msgId = 100;
                packet << msgId << msgId << mEntities[i] << mvt;
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
                sf::Int32 msgId = 100;
                packet << msgId << msgId << mEntities[i] << mvt;
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
                sf::Int32 msgId = 100;
                packet << msgId << msgId << mEntities[i] << mvt;
                mEntityManager->sendPacket(packet);
            }
        }
    }
}

void MovementSystem::collision(sf::Int32 const& entityId)
{
    BaseComponent& c = mEntityManager->getComponent<BaseComponent>(entityId);

    ses::ComponentFilter filter;
    filter.requires(BaseComponent::getId());
    std::vector<sf::Int32> entities = mEntityManager->getEntities(filter);

    for (std::size_t i = 0; i < entities.size(); i++)
    {
        if (entities[i] != entityId)
        {
            BaseComponent& c2 = mEntityManager->getComponent<BaseComponent>(entities[i]);
            if (c2.intersects(c))
            {
                handleCollision(entityId,entities[i]);
            }
        }
    }
}

void MovementSystem::handleCollision(sf::Int32 const& entity1, sf::Int32 const& entity2)
{
    if (mEntityManager->hasComponent<PlanetComponent>(entity1))
    {
        if (mEntityManager->hasComponent<ShipComponent>(entity2))
        {
            // Remove entity2
            sf::Packet packet;
            sf::Int32 msgId = 203;
            packet << msgId << msgId << entity2;
            mEntityManager->sendPacket(packet);
        }
        else if (mEntityManager->hasComponent<PlanetComponent>(entity2))
        {
            // Strange ?
        }
        else if (mEntityManager->hasComponent<CometComponent>(entity2))
        {
            // Remove entity2
            sf::Packet packet;
            sf::Int32 msgId = 203;
            packet << msgId << msgId << entity2;
            mEntityManager->sendPacket(packet);
        }
    }
    else if (mEntityManager->hasComponent<ShipComponent>(entity1))
    {
        if (mEntityManager->hasComponent<PlanetComponent>(entity2))
        {
            // Remove entity1
            sf::Packet packet;
            sf::Int32 msgId = 203;
            packet << msgId << msgId << entity1;
            mEntityManager->sendPacket(packet);
        }
        else if (mEntityManager->hasComponent<ShipComponent>(entity2))
        {
            // Apply Damage to both
        }
        else if (mEntityManager->hasComponent<CometComponent>(entity2))
        {
            // Apply Damage to both
        }
    }
    else if (mEntityManager->hasComponent<CometComponent>(entity1))
    {
        if (mEntityManager->hasComponent<PlanetComponent>(entity2))
        {
            // Remove entity1
            sf::Packet packet;
            sf::Int32 msgId = 203;
            packet << msgId << msgId << entity1;
            mEntityManager->sendPacket(packet);
        }
        else if (mEntityManager->hasComponent<ShipComponent>(entity2))
        {
            // Apply Damage to both
        }
        else if (mEntityManager->hasComponent<CometComponent>(entity2))
        {
            // Apply Damage to both
        }
    }

}

void MovementSystem::handlePacket(sf::Packet& packet)
{
    if (mEntityManager == nullptr)
        return;

    sf::Int32 eventId;
    packet >> eventId;
    switch (eventId)
    {
        case 100:
        {
            sf::Int32 entityId;
            sf::Vector2f mvt;
            packet >> entityId >> mvt;

            // Move the entity
            if (mEntityManager->hasComponent<BaseComponent>(entityId))
            {
                mEntityManager->getComponent<BaseComponent>(entityId).move(mvt);

                // Collision
                collision(entityId);
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
            if (mEntityManager->hasComponent<BaseComponent>(entityId))
            {
                mEntityManager->getComponent<BaseComponent>(entityId).setRotation(rotation);
            }
        } break;

        default: break;
    }
}
