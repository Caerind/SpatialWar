#ifndef SHIPPARTSYSTEM_HPP
#define SHIPPARTSYSTEM_HPP

#include "../../Lib/EntitySystem/System.hpp"

#include "../Components.hpp"

class ShipPartSystem : public ses::System
{
    public:
        ShipPartSystem(std::shared_ptr<ses::EntityManager> entityManager);

        static std::string getId();

        void update();

        void changeMotor(sf::Int32 const& entityId, int motorId);
        void changeArmor(sf::Int32 const& entityId, int armorId);
        void changeGun(sf::Int32 const& entityId, int gunId);

        void handlePacket(sf::Packet& packet);
};

#endif // SHIPPARTSYSTEM_HPP
