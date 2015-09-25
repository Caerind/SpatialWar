#ifndef SES_SYSTEMMANAGER_HPP
#define SES_SYSTEMMANAGER_HPP

#include <map>
#include <memory>

#include "Packet.hpp"
#include "System.hpp"

namespace ses
{

class EntityManager;

class SystemManager
{
    public:
        SystemManager(std::shared_ptr<EntityManager> entityManager);
        ~SystemManager();

        template<typename T, typename ... Args>
        T& addSystem(Args&& ... args);

        template<typename T>
        bool hasSystem();
        bool hasSystem(std::string const& systemId);

        template<typename T>
        T& getSystem();

        template<typename T>
        void removeSystem();
        void removeSystems();

        void handlePacket(std::string const& systemId, sf::Packet& packet);
        void entityUpdate(sf::Int32 const& entityId);

    protected:
        std::shared_ptr<EntityManager> mEntityManager;
        std::map<std::string,System::Ptr> mSystems;
};



template<typename T, typename ... Args>
T& SystemManager::addSystem(Args&& ... args)
{
    mSystems[T::getId()] = std::unique_ptr<T>(new T(mEntityManager, std::forward<Args>(args)...));
    return getSystem<T>();
}

template<typename T>
bool SystemManager::hasSystem()
{
    return mSystems.find(T::getId()) != mSystems.end();
}

template<typename T>
void SystemManager::removeSystem()
{
    auto itr = mSystems.find(T::getId());
    if (itr != mSystems.end())
    {
        itr->second = nullptr;
        mSystems.erase(itr);
    }
}

template<typename T>
T& SystemManager::getSystem()
{
    assert(hasSystem<T>());
    return static_cast<T&>(*mSystems.at(T::getId()));
}

} // namespace ses

#endif // SES_SYSTEMMANAGER_HPP
