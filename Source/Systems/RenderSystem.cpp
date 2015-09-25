#include "RenderSystem.hpp"
#include "../../Lib/EntitySystem/EntityManager.hpp"

RenderSystem::RenderSystem(ses::EntityManager::Ptr entityManager)
: System(entityManager)
{
}

std::string RenderSystem::getId()
{
    return "RenderSystem";
}

void RenderSystem::render(sf::RenderTarget& target, sf::RenderStates states)
{
    for (std::size_t i = 0; i < mEntities.size(); i++)
    {
        if (mEntityManager->hasComponent<SpriteComponent>(mEntities[i]))
        {
            target.draw(mEntityManager->getComponent<SpriteComponent>(mEntities[i]));
        }
    }
}

void RenderSystem::handlePacket(sf::Packet& packet)
{
    int eventId;
    packet >> eventId;
    switch (eventId)
    {
        default: break;
    }
}
