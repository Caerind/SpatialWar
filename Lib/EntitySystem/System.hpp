#ifndef SES_SYSTEM_HPP
#define SES_SYSTEM_HPP

#include <memory>
#include <string>
#include <vector>

#include "ComponentFilter.hpp"
#include "Packet.hpp"

namespace ses
{

class EntityManager;

class System
{
    public:
        System(std::shared_ptr<EntityManager> entityManager);
        virtual ~System();

        typedef std::unique_ptr<System> Ptr;

        static std::string getId();

        virtual void handlePacket(sf::Packet& packet);
        void entityUpdate(sf::Int32 const& entityId);

        std::size_t entitiesCount() const;

    protected:
        std::shared_ptr<EntityManager> mEntityManager;
        std::vector<sf::Int32> mEntities;
        ComponentFilter mFilter;
};

} // namespace ses

#endif // SES_SYSTEM_HPP
