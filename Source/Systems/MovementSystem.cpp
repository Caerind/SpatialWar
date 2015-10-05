#include "MovementSystem.hpp"
#include "../../Lib/EntitySystem/EntityManager.hpp"
#include "../../Lib/Aharos/Helper/Math.hpp"
#include "../World.hpp"

MovementSystem::MovementSystem(ses::EntityManager::Ptr entityManager)
: ses::System(entityManager)
{
    mFilter.requires(BaseComponent::getId());
}

std::string MovementSystem::getId()
{
    return "MovementSystem";
}

void MovementSystem::update(sf::Time dt)
{
    if (mEntityManager == nullptr)
        return;

    ses::ComponentFilter filterPlanets;
    filterPlanets.requires(BaseComponent::getId());
    filterPlanets.requires(PlanetComponent::getId());
    auto planets = mEntityManager->getEntities(filterPlanets);

    for (std::size_t i = 0; i < mEntities.size(); i++)
    {
        BaseComponent& b = mEntityManager->getComponent<BaseComponent>(mEntities[i]);

        // MRU
        if (mEntityManager->hasComponent<CometComponent>(mEntities[i])
        || mEntityManager->hasComponent<BulletComponent>(mEntities[i]))
        {
            sendMovement(mEntities[i], b.getDirection() * b.getSpeed() * dt.asSeconds());
        }

        // MRU with speed reduction
        if (mEntityManager->hasComponent<AsteroidComponent>(mEntities[i])
        || mEntityManager->hasComponent<ResourceComponent>(mEntities[i]))
        {
            /*if (b.getSpeed() > 0.f)
            {
                sf::Packet packet;
                sf::Int32 msgId = 212;
                packet << msgId << msgId << mEntities[i] << -25.f * dt.asSeconds();
                mEntityManager->sendPacket(packet);
            }*/
            sendMovement(mEntities[i], b.getDirection() * b.getSpeed() * dt.asSeconds());
        }

        if (!mEntityManager->hasComponent<PlanetComponent>(mEntities[i]))
        {
            /*
            // Uncomment if we don't want planet attraction on bullets
            if (!mEntityManager->hasComponent<BulletComponent>(mEntities[i]))
            {
            */
            for (std::size_t j = 0; j < planets.size(); j++)
            {
                sf::Vector2f pPos = mEntityManager->getComponent<BaseComponent>(planets[j]).getPosition();
                float m = mEntityManager->getComponent<BaseComponent>(planets[j]).getMass();
                float g = 2.f * pow(10,-11); // g is modified to fit in the game

                sf::Vector2f diff = pPos - b.getPosition();
                float d = lp::length(diff);
                if (d < 10000.f)
                {
                    d *= 100.f; // add a constant to fit in the game
                    sf::Vector2f u = lp::unitVector(diff);
                    sf::Vector2f mvt = u * g * m * dt.asSeconds() / (d * d);

                    bool stationary = false;
                    if (mEntityManager->hasComponent<ShipComponent>(mEntities[i]))
                    {
                        if (mEntityManager->getComponent<ShipComponent>(mEntities[i]).isStationary())
                        {
                            stationary = true;
                        }
                    }

                    if (!stationary)
                    {
                        sendMovement(mEntities[i],mvt);
                    }
                }
            }

            /*
            // Uncomment if we don't want planet attraction on bullets
            }
            */

        }
    }
}

void MovementSystem::sendMovement(sf::Int32 const& entityId, sf::Vector2f const& movement)
{
    if (movement != sf::Vector2f(0.f,0.f))
    {
        if (lp::length(movement) >= 0.01f)
        {
            sf::Packet packet;
            sf::Int32 msgId = 100;
            packet << msgId << msgId << entityId << movement;
            World::getEntities().sendPacket(packet);
        }
    }
}

void MovementSystem::sendPosition(sf::Int32 const& entityId, sf::Vector2f const& position)
{
    sf::Packet packet;
    sf::Int32 msgId = 101;
    packet << msgId << msgId << entityId << position;
    World::getEntities().sendPacket(packet);
}

void MovementSystem::sendRotation(sf::Int32 const& entityId, float angle)
{
    sf::Packet packet;
    sf::Int32 msgId = 102;
    packet << msgId << msgId << entityId << angle;
    World::getEntities().sendPacket(packet);
}

void MovementSystem::sendStationary(sf::Int32 const& entityId, bool stationary)
{
    sf::Packet packet;
    sf::Int32 msgId = 103;
    packet << msgId << msgId << entityId << stationary;
    World::getEntities().sendPacket(packet);
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
            std::cout << "Collision : " << msgId << std::endl;
        }
        else if (mEntityManager->hasComponent<PlanetComponent>(entity2))
        {
            // Strange ?
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
            std::cout << "Collision : " << msgId << std::endl;
        }
        else if (mEntityManager->hasComponent<ShipComponent>(entity2))
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
        case 100: // Movement
        {
            sf::Int32 entityId;
            sf::Vector2f mvt;
            packet >> entityId >> mvt;

            if (mEntityManager->hasComponent<BaseComponent>(entityId))
            {
                mEntityManager->getComponent<BaseComponent>(entityId).move(mvt);

                collision(entityId);
            }

            if (mEntityManager->hasComponent<PlayerComponent>(entityId))
            {
                mEntityManager->getComponent<PlayerComponent>(entityId).getView().move(mvt);
            }
        } break;

        case 101: // Position
        {
            sf::Int32 entityId;
            sf::Vector2f position;
            packet >> entityId >> position;

            if (mEntityManager->hasComponent<BaseComponent>(entityId))
            {
                mEntityManager->getComponent<BaseComponent>(entityId).setPosition(position);
            }

            if (mEntityManager->hasComponent<PlayerComponent>(entityId))
            {
                mEntityManager->getComponent<PlayerComponent>(entityId).getView().setCenter(position);
            }
        } break;

        case 102: // Rotation
        {
            sf::Int32 entityId;
            float rotation;
            packet >> entityId >> rotation;

            if (mEntityManager->hasComponent<BaseComponent>(entityId))
            {
                mEntityManager->getComponent<BaseComponent>(entityId).setRotation(rotation);
            }
        } break;

        case 103: // Stationary
        {
            sf::Int32 entityId;
            bool stationary;
            packet >> entityId >> stationary;
            if (mEntityManager->hasComponent<ShipComponent>(entityId))
            {
                mEntityManager->getComponent<ShipComponent>(entityId).setStationary(stationary);
            }
        } break;

        default: break;
    }
}
