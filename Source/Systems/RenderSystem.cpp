#include "RenderSystem.hpp"
#include "../../Lib/EntitySystem/EntityManager.hpp"

RenderSystem::RenderSystem(ses::EntityManager::Ptr entityManager)
: ses::System(entityManager)
{
    mFilter.requires(SpriteComponent::getId());
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
            SpriteComponent& s = mEntityManager->getComponent<SpriteComponent>(mEntities[i]);
            if (mEntityManager->hasComponent<TransformComponent>(mEntities[i]))
            {
                TransformComponent& t = mEntityManager->getComponent<TransformComponent>(mEntities[i]);
                s.setOrigin(t.getOrigin());
                s.setPosition(t.getPosition());
                s.setRotation(t.getRotation());
                s.setScale(t.getScale());
            }
            target.draw(s);
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
