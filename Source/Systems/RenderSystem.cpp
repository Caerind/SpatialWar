#include "RenderSystem.hpp"
#include "../../Lib/EntitySystem/EntityManager.hpp"

RenderSystem::RenderSystem(ses::EntityManager::Ptr entityManager)
: ses::System(entityManager)
{
    mFilter.requires(TransformComponent::getId());
    std::vector<std::string> renderableComponents;
    renderableComponents.push_back(ShipComponent::getId());
    renderableComponents.push_back(PlanetComponent::getId());
    renderableComponents.push_back(CometComponent::getId());
    renderableComponents.push_back(AsteroidComponent::getId());
    renderableComponents.push_back(BulletComponent::getId());
    renderableComponents.push_back(ResourceComponent::getId());
    mFilter.requiresOne(renderableComponents);
}

std::string RenderSystem::getId()
{
    return "RenderSystem";
}

void RenderSystem::render(sf::RenderTarget& target, sf::RenderStates states)
{
    if (mEntityManager == nullptr)
        return;

    for (std::size_t i = 0; i < mEntities.size(); i++)
    {
        sf::RenderStates entStates = states;
        entStates.transform *= mEntityManager->getComponent<TransformComponent>(mEntities[i]).getTransform();

        if (mEntityManager->hasComponent<ShipComponent>(mEntities[i]))
        {
            target.draw(mEntityManager->getComponent<ShipComponent>(mEntities[i]),entStates);
        }
        else if (mEntityManager->hasComponent<PlanetComponent>(mEntities[i]))
        {
            target.draw(mEntityManager->getComponent<PlanetComponent>(mEntities[i]),entStates);
        }
        else if (mEntityManager->hasComponent<CometComponent>(mEntities[i]))
        {
            target.draw(mEntityManager->getComponent<CometComponent>(mEntities[i]),entStates);
        }
        else if (mEntityManager->hasComponent<BulletComponent>(mEntities[i]))
        {
            target.draw(mEntityManager->getComponent<BulletComponent>(mEntities[i]),entStates);
        }
        else if (mEntityManager->hasComponent<AsteroidComponent>(mEntities[i]))
        {
            target.draw(mEntityManager->getComponent<AsteroidComponent>(mEntities[i]),entStates);
        }
        else if (mEntityManager->hasComponent<ResourceComponent>(mEntities[i]))
        {
            target.draw(mEntityManager->getComponent<ResourceComponent>(mEntities[i]),entStates);
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
