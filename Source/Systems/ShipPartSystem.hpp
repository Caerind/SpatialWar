#ifndef SHIPPARTSYSTEM_HPP
#define SHIPPARTSYSTEM_HPP

#include "../../Lib/EntitySystem/System.hpp"

#include "../Components.hpp"

class ShipPartSystem : public ses::System
{
    public:
        ShipPartSystem(std::shared_ptr<ses::EntityManager> entityManager);

        static std::string getId();

        void changeMotor(sf::Int32 const& entityId, int motorId);
        void changeArmor(sf::Int32 const& entityId, int armorId);
        void changeGun(sf::Int32 const& entityId, int gunId);

        static float getMotorSpeed(int motorId);
        static float getMotorMass(int motorId);
        static float getArmor(int armorId);
        static float getArmorMass(int armorId);
        static float getGunStrength(int gunId);
        static float getGunMass(int gunId);

        void handlePacket(sf::Packet& packet);
};

#endif // SHIPPARTSYSTEM_HPP
