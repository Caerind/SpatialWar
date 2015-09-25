#ifndef SES_ENTITYMANAGER_HPP
#define SES_ENTITYMANAGER_HPP

#include <cassert>
#include <functional>
#include <map>
#include <memory>
#include <vector>

#include <SFML/System.hpp>

#include "Component.hpp"
#include "Packet.hpp"
#include "SystemManager.hpp"

namespace ses
{

class EntityManager
{
    public:
        typedef std::shared_ptr<EntityManager> Ptr;
        typedef std::function<sf::Int32()> Prefab;

        friend SystemManager; // This allow the SystemManager to set himself as the mSystems variable.

        EntityManager();
        ~EntityManager();

        // Entity Management

        sf::Int32 addEntity();
        sf::Int32 addEntity(sf::Int32 const& entityId);
        bool hasEntity(sf::Int32 const& entityId);
        void removeEntity(sf::Int32 const& entityId);
        void removeEntities();
        std::size_t entitiesCount() const;

        template<typename T, typename ... Args>
        T& addComponent(sf::Int32 const& entityId, Args&& ... args);

        template<typename T>
        bool hasComponent(sf::Int32 const& entityId);
        bool hasComponent(sf::Int32 const& entityId, std::string const& componentId);

        template<typename T>
        T& getComponent(sf::Int32 const& entityId);

        template<typename T>
        void removeComponent(sf::Int32 const& entityId);
        void removeComponents(sf::Int32 const& entityId);

        void setPrefab(std::string const& prefabId, Prefab ctor);
        sf::Int32 usePrefab(std::string const& prefabId);

        // Event Management

        virtual void sendPacket(sf::Packet& packet);
        virtual void handlePackets();
        virtual void handlePacket(sf::Packet& packet);

    protected:
        SystemManager* mSystems;

        // Entity Management
        std::map<sf::Int32,std::map<std::string,Component::Ptr>> mComponents;
        sf::Int32 mId;
        std::map<std::string,Prefab> mPrefabs;

        // Event Management
        sf::Thread mEventThread;
        sf::Mutex mMutex;
        bool mRunning;
        std::vector<sf::Packet> mPackets;
};

template<typename T, typename ... Args>
T& EntityManager::addComponent(sf::Int32 const& entityId, Args&& ... args)
{
    assert(hasEntity(entityId));

    mComponents.at(entityId)[T::getId()] = std::unique_ptr<T>(new T(std::forward<Args>(args)...));

    if (mSystems != nullptr)
    {
        mSystems->entityUpdate(entityId);
    }

    return getComponent<T>(entityId);
}

template<typename T>
bool EntityManager::hasComponent(sf::Int32 const& entityId)
{
    assert(hasEntity(entityId));
    return mComponents.at(entityId).find(T::getId()) != mComponents.at(entityId).end();
}

template<typename T>
void EntityManager::removeComponent(sf::Int32 const& entityId)
{
    assert(hasEntity(entityId));

    auto itr = mComponents.at(entityId).find(T::getId());
    if (itr != mComponents.at(entityId).end())
    {
        mComponents.at(entityId).erase(itr);

        if (mSystems != nullptr)
        {
            mSystems->entityUpdate(entityId);
        }
    }
}

template<typename T>
T& EntityManager::getComponent(sf::Int32 const& entityId)
{
    assert(hasEntity(entityId));
    assert(hasComponent<T>(entityId));
    return static_cast<T&>(*mComponents.at(entityId).at(T::getId()));
}

} // namespace ses

#endif // SES_ENTITYMANAGER_HPP
