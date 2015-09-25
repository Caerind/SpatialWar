#include "SystemManager.hpp"
#include "EntityManager.hpp"

namespace ses
{

SystemManager::SystemManager(EntityManager::Ptr entityManager)
: mEntityManager(entityManager)
{
    if (mEntityManager != nullptr)
    {
        mEntityManager->mSystems = this;
    }
}

SystemManager::~SystemManager()
{
    removeSystems();
    mEntityManager->mSystems = nullptr;
}

bool SystemManager::hasSystem(std::string const& systemId)
{
    return mSystems.find(systemId) != mSystems.end();
}

void SystemManager::removeSystems()
{
    mSystems.clear();
}

void SystemManager::handlePacket(std::string const& systemId, sf::Packet& packet)
{
    if (hasSystem(systemId))
    {
        mSystems.at(systemId)->handlePacket(packet);
    }
}

void SystemManager::entityUpdate(sf::Int32 const& entityId)
{
    for (auto itr = mSystems.begin(); itr != mSystems.end(); itr++)
    {
        itr->second->entityUpdate(entityId);
    }
}

} // namespace ses
