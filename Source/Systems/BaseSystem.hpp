#ifndef BASESYSTEM_HPP
#define BASESYSTEM_HPP

#include "../../Lib/EntitySystem/System.hpp"

#include "../Components.hpp"

class BaseSystem : public ses::System
{
    public:
        BaseSystem(std::shared_ptr<ses::EntityManager> entityManager);

        static std::string getId();

        void update();

        void handlePacket(sf::Packet& packet);
};

#endif // BASESYSTEM_HPP
