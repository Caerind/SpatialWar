#include "ComponentFilter.hpp"
#include "EntityManager.hpp"

namespace ses
{

ComponentFilter::ComponentFilter()
{
}

ComponentFilter::~ComponentFilter()
{
    mRequiredComponents.clear();
    mExcludedComponents.clear();
    mRequiredOneComponents.clear();
}

void ComponentFilter::requires(std::string const& componentId)
{
    mRequiredComponents.push_back(componentId);
}

void ComponentFilter::excludes(std::string const& componentId)
{
    mExcludedComponents.push_back(componentId);
}

void ComponentFilter::requiresOne(std::vector<std::string> componentIds)
{
    mRequiredOneComponents.push_back(componentIds);
}

bool ComponentFilter::passFilter(sf::Int32 const& entityId, EntityManager::Ptr em)
{
    if (em == nullptr)
    {
        return false;
    }
    if (!em->hasEntity(entityId))
    {
        return false;
    }
    std::size_t size = mRequiredComponents.size();
    for (std::size_t i = 0; i < size; i++)
    {
        if (!em->hasComponent(entityId, mRequiredComponents[i]))
        {
            return false;
        }
    }
    size = mExcludedComponents.size();
    for (std::size_t i = 0; i < size; i++)
    {
        if (em->hasComponent(entityId, mExcludedComponents[i]))
        {
            return false;
        }
    }
    size = mRequiredOneComponents.size();
    for (std::size_t i = 0; i < size; i++)
    {
        std::size_t size2 = mRequiredOneComponents[i].size();
        bool found = false;
        for (std::size_t j = 0; j < size2; j++)
        {
            if (em->hasComponent(entityId, mRequiredOneComponents[i][j]))
            {
                found = true;
            }
        }
        if (!found)
        {
            return false;
        }
    }
    return true;
}

} // namespace ses
