#include "EntityManager.hpp"
#include "SystemManager.hpp"

namespace ses
{

EntityManager::EntityManager()
{
    mSystems = nullptr;
    mId = 0;
}

EntityManager::~EntityManager()
{
    if (mSystems != nullptr)
    {
        mSystems->removeSystems();
        mSystems = nullptr;
    }
    removeEntities();
}

sf::Int32 EntityManager::addEntity()
{
    mComponents[++mId].clear();
    return mId;
}

sf::Int32 EntityManager::addEntity(sf::Int32 const& entityId)
{
    mComponents[entityId].clear();
    return entityId;
}

std::vector<sf::Int32> EntityManager::getEntities(ComponentFilter& filter)
{
    std::vector<sf::Int32> entities;
    for (auto itr = mComponents.begin(); itr != mComponents.end(); itr++)
    {
        if (filter.passFilter(itr->first,this))
        {
            entities.push_back(itr->first);
        }
    }
    return entities;
}

bool EntityManager::hasEntity(sf::Int32 const& entityId)
{
    return mComponents.find(entityId) != mComponents.end();
}

void EntityManager::removeEntity(sf::Int32 const& entityId)
{
    auto itr = mComponents.find(entityId);
    if (itr != mComponents.end())
    {
        removeComponents(entityId);
        mComponents.erase(itr);
    }
}

void EntityManager::removeEntities()
{
    for (auto itr = mComponents.begin(); itr != mComponents.end(); itr++)
    {
        itr->second.clear();
        if (mSystems != nullptr)
        {
            mSystems->entityUpdate(itr->first);
        }
    }
    mComponents.clear();
}

std::size_t EntityManager::entitiesCount() const
{
    return mComponents.size();
}

bool EntityManager::hasComponent(sf::Int32 const& entityId, std::string const& componentId)
{
    if (hasEntity(entityId))
    {
        return mComponents.at(entityId).find(componentId) != mComponents.at(entityId).end();
    }
    return false;
}

bool EntityManager::hasComponents(sf::Int32 const& entityId, ComponentFilter& filter)
{
    return filter.passFilter(entityId,this);
}

void EntityManager::removeComponents(sf::Int32 const& entityId)
{
    auto itr = mComponents.find(entityId);
    if (itr != mComponents.end())
    {
        itr->second.clear();
        if (mSystems != nullptr)
        {
            mSystems->entityUpdate(entityId);
        }
    }
}

void EntityManager::setPrefab(std::string const& prefabId, Prefab ctor)
{
    mPrefabs[prefabId] = ctor;
}

sf::Int32 EntityManager::usePrefab(std::string const& prefabId)
{
    if (mPrefabs.find(prefabId) != mPrefabs.end())
    {
        if (mPrefabs.at(prefabId))
        {
            return mPrefabs.at(prefabId)();
        }
    }
    return 0;
}

void EntityManager::sendPacket(sf::Packet& packet)
{
    mPackets.push_back(packet);
}

void EntityManager::handlePackets()
{
    while (!mPackets.empty() && mSystems != nullptr)
    {
        handlePacket(mPackets.back());
        mPackets.pop_back();
    }
    mPackets.clear();
}

void EntityManager::handlePacket(sf::Packet& packet)
{
}

} // namespace ses
