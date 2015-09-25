#include "System.hpp"
#include "EntityManager.hpp"

namespace ses
{

System::System(EntityManager::Ptr entityManager)
: mEntityManager(entityManager)
{
}

System::~System()
{
}

std::string System::getId()
{
    return "System";
}

void System::handlePacket(sf::Packet& packet)
{
}

void System::entityUpdate(sf::Int32 const& entityId)
{
    bool found = false;
    std::size_t foundPos = 0;
    std::size_t size = mEntities.size();
    for (std::size_t i = 0; i < size; i++)
    {
        if (mEntities[i] == entityId)
        {
            found = true;
            foundPos = i;
        }
    }
    if (mFilter.passFilter(entityId, mEntityManager) && !found)
    {
        mEntities.push_back(entityId);
    }
    else if (!mFilter.passFilter(entityId, mEntityManager) && found)
    {
        mEntities.erase(mEntities.begin() + foundPos);
    }
}

std::size_t System::entitiesCount() const
{
    return mEntities.size();
}

} // namespace ses
