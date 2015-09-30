#include "PlanetAttractionSystem.hpp"
#include "../../Lib/EntitySystem/EntityManager.hpp"
#include "../World.hpp"
#include "../../Lib/Aharos/Helper/Math.hpp"

PlanetAttractionSystem::PlanetAttractionSystem(ses::EntityManager::Ptr entityManager)
: ses::System(entityManager)
{
    mFilter.requires(BaseComponent::getId());
    mFilter.requires(PlanetComponent::getId());
}

std::string PlanetAttractionSystem::getId()
{
    return "PlanetAttractionSystem";
}

void PlanetAttractionSystem::update(sf::Time dt)
{
    if (mEntityManager == nullptr)
        return;

    ses::ComponentFilter filter;
    filter.requires(BaseComponent::getId());
    std::vector<std::string> attractableEntities;
    attractableEntities.push_back(CometComponent::getId());
    attractableEntities.push_back(AsteroidComponent::getId());
    attractableEntities.push_back(ShipComponent::getId());
    attractableEntities.push_back(ResourceComponent::getId());
    filter.requiresOne(attractableEntities);

    std::vector<sf::Int32> entities = mEntityManager->getEntities(filter);

    for (std::size_t i = 0; i < mEntities.size(); i++)
    {
        /*
        sf::Vector2f pPos = mEntityManager->getComponent<BaseComponent>(mEntities[i]).getPosition();
        float m = mEntityManager->getComponent<BaseComponent>(mEntities[i]).getMass();
        float g = 6.67f * 100.f;
        for (std::size_t j = 0; j < entities.size(); j++)
        {
            sf::Vector2f diff = pPos - mEntityManager->getComponent<BaseComponent>(entities[j]).getPosition();
            float d = lp::length(diff) - mEntityManager->getComponent<PlanetComponent>(mEntities[i]).getRadius() - 300.f;
            sf::Vector2f u = lp::unitVector(diff);
            sf::Vector2f mvt = 1.9f * u + u * g * m * dt.asSeconds() / (d * d);

            bool stationary = false;
            if (mEntityManager->hasComponent<ShipComponent>(entities[j]))
            {
                if (mEntityManager->getComponent<ShipComponent>(entities[j]).isStationary())
                {
                    stationary = true;
                }
            }

            if ((std::abs(mvt.x) > 1.5f || std::abs(mvt.y) > 1.5f) && !stationary)
            {
                sf::Packet packet;
                packet << 100 << 100 << entities[j] << mvt;
                mEntityManager->sendPacket(packet);
            }
            std::cout << "Planet Attraction : " << mvt.x << " " << mvt.y << std::endl;
        }
        */
    }
}
