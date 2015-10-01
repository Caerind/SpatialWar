#include "BaseSystem.hpp"
#include "../../Lib/EntitySystem/EntityManager.hpp"
#include "../../Lib/Aharos/Application/Application.hpp"

BaseSystem::BaseSystem(ses::EntityManager::Ptr entityManager)
: ses::System(entityManager)
{
    mFilter.requires(BaseComponent::getId());
}

std::string BaseSystem::getId()
{
    return "BaseSystem";
}

void BaseSystem::update()
{
    for (std::size_t i = 0; i < mEntities.size(); i++)
    {


        // Remove Dead Entities
        if (mEntityManager->getComponent<BaseComponent>(mEntities[i]).isDead())
        {
            if (mEntityManager->hasComponent<PlayerComponent>(mEntities[i]))
            {
                mEntityManager->getComponent<BaseComponent>(mEntities[i]).restoreFullLife();
                mEntityManager->getComponent<BaseComponent>(mEntities[i]).setPosition(sf::Vector2f(2500.f,2500.f));
                std::cout << "ok" << std::endl;
            }
            else
            {
                mEntityManager->removeEntity(mEntities[i]);
                std::cout << "ok" << std::endl;
            }
        }
    }
}

void BaseSystem::handlePacket(sf::Packet& packet)
{
    if (mEntityManager == nullptr)
        return;

    sf::Int32 eventId;
    packet >> eventId;
    switch (eventId)
    {
        case 200:
        {
            sf::Int32 entityId;
            float life;
            packet >> entityId >> life;
            if (mEntityManager->hasComponent<BaseComponent>(entityId))
            {
                mEntityManager->getComponent<BaseComponent>(entityId).setLife(life);
            }
        } break;

        case 201:
        {
            sf::Int32 entityId;
            float damage;
            packet >> entityId >> damage;
            if (mEntityManager->hasComponent<BaseComponent>(entityId))
            {
                mEntityManager->getComponent<BaseComponent>(entityId).inflige(damage);
            }
        } break;

        case 202:
        {
            sf::Int32 entityId;
            float restore;
            packet >> entityId >> restore;
            if (mEntityManager->hasComponent<BaseComponent>(entityId))
            {
                mEntityManager->getComponent<BaseComponent>(entityId).restore(restore);
            }
        } break;

        case 203:
        {
            sf::Int32 entityId;
            packet >> entityId;
            if (mEntityManager->hasComponent<BaseComponent>(entityId))
            {
                mEntityManager->getComponent<BaseComponent>(entityId).setLife(0.f);
            }
        } break;

        case 204:
        {
            sf::Int32 entityId;
            packet >> entityId;
            if (mEntityManager->hasComponent<BaseComponent>(entityId))
            {
                mEntityManager->getComponent<BaseComponent>(entityId).restoreFullLife();
            }
        } break;

        default: break;
    }
}
